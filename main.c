#include <stdio.h>
#include "scheduler.h"

int main() {
    PriorityQueue *api_gateway = create_queue(10);

    // Test Senaryosu: Karışık önceliklerde istekler geliyor
    printf("--- İstekler Kuyruğa Alınıyor ---\n");

    HttpRequest reqs[] = {
        {101, 3, "GET", "/images/logo.png"},
        {102, 0, "POST", "/api/login"},      // En yüksek öncelik (RFC 9213 u=0)
        {103, 7, "GET", "/ads/banner"},     // En düşük öncelik (u=7)
        {104, 1, "POST", "/api/payment"}     // Yüksek öncelik
    };

    for(int i = 0; i < 4; i++) {
        printf("Push: ID %d (Urgency: %d)\n", reqs[i].request_id, reqs[i].urgency);
        push_request(api_gateway, reqs[i]);
    }

    printf("\n--- API Gateway İşleme Sırası (Min-Heap Çıktısı) ---\n");
    while (api_gateway->size > 0) {
        HttpRequest current = pop_request(api_gateway);
        printf("Processing ID: %d | Urgency: %d | Method: %s | Path: %s\n",
               current.request_id, current.urgency, current.method, current.path);
    }

    free_queue(api_gateway);
    return 0;
}