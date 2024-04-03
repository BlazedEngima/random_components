#include <curl/curl.h>
#include <mysqlx/xdevapi.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>

std::string create_signature(const std::string &data, const std::string &key) {
  unsigned char *digest =
      HMAC(EVP_sha256(), key.c_str(), key.length(),
           (unsigned char *)data.c_str(), data.length(), NULL, NULL);

  char mdString[SHA256_DIGEST_LENGTH * 2 + 1];
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

  return std::string(mdString);
}

void send_post_request(const std::string &url, const std::string &post_fields,
                       const std::string &api_key,
                       const std::string &api_secret) {
  CURL *curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = NULL;

    // Add API key to headers
    headers = curl_slist_append(headers, ("X-MBX-APIKEY: " + api_key).c_str());

    // Create the signature and append it to the payload
    std::string signature = create_signature(post_fields, api_secret);
    std::string payload = post_fields + "&signature=" + signature;

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

    // Perform the request
    curl_easy_perform(curl);

    // Clean up
    curl_easy_cleanup(curl);
  }
}
int main() {
  mysqlx::Session sess("localhost", 3306, "user", "password");

  while (true) {
    // Fetch order information
    mysqlx::Table event_queue =
        sess.getSchema("your_database").getTable("event_queue");
    mysqlx::RowResult res = event_queue.select("*").limit(100).execute();

    // If there are no more rows, break the loop
    if (res.count() == 0) {
      break;
    }

    for (const mysqlx::Row &row : res) {
      std::string client_order_id = row[0].get<std::string>();
      std::string symbol = row[1].get<std::string>();
      std::string side = row[2].get<std::string>();
      std::string qty = row[3].get<std::string>();
      std::string price = row[4].get<std::string>();

      // Construct the POST fields
      std::string post_fields = "clientOrderId=" + client_order_id +
                                "&symbol=" + symbol + "&side=" + side +
                                "&qty=" + qty + "&price=" + price;

      // Send a POST request to Binance Futures API
      send_post_request("https://fapi.binance.com/fapi/v1/order", post_fields,
                        "your_api_key", "your_api_secret");

      // Delete the processed row
      event_queue.remove()
          .where("client_order_id = :param")
          .bind("param", client_order_id)
          .execute();
    }
  }

  return 0;
}