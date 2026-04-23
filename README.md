# RFC 9213 Uyumlu Modüler API Gateway İstek Zamanlayıcısı

Bu proje, modern API Gateway sistemlerinde gelen HTTP isteklerini **RFC 9213 (Extensible HTTP Priorities)** standartlarına göre önceliklendiren, yüksek performanslı bir **Priority Request Scheduler** (İstek Zamanlayıcısı) uygulamasıdır. Sistem, verimliliği maksimize etmek için **Min-Heap** veri yapısını ve C dilinin sunduğu modüler programlama mimarisini kullanır.

## 🚀 Proje Özellikleri

* **RFC 9213 Uyumu:** İstekler `urgency` (u=0 ile u=7) parametrelerine göre standardize edilmiş şekilde parse edilir ve işlenir.
* **Modüler Mimari:** Veri modelleri (`.h`), algoritma mantığı (`.c`) ve uygulama katmanı birbirinden tamamen izole edilmiştir (Separation of Concerns).
* **Yüksek Performans:** Min-Heap veri yapısı sayesinde en öncelikli elemana erişim $O(1)$, ekleme ve silme işlemleri $O(\log n)$ karmaşıklığında gerçekleşir.
* **Dinamik Ölçeklenebilirlik:** `realloc` mekanizması ile bellek, gelen trafik yüküne göre dinamik olarak genişletilir.
* **Güvenli Bellek Yönetimi:** Pointer güvenliği esas alınmış olup, işlem sonunda tüm kaynaklar `free()` ile iade edilerek sıfır bellek sızıntısı hedeflenmiştir.

---

## 🏗️ Sistem Mimarisi ve Dosya İlişkileri

Proje, sürdürülebilirlik ve test edilebilirlik için 4 ana parçaya bölünmüştür:

| Dosya | Katman | Açıklama |
| :--- | :--- | :--- |
| `priority_levels.h` | **Veri Katmanı** | RFC 9213 standartlarını içeren `HttpRequest` struct yapısını tanımlar. |
| `scheduler.h` | **Arayüz (Interface)** | Kuyruk yönetimi fonksiyon prototiplerini ve `PriorityQueue` yönetim yapısını içerir. |
| `scheduler.c` | **Mantık (Logic)** | Min-Heap algoritmasının (HeapifyUp, HeapifyDown, Swap) çekirdek implementasyonudur. |
| `main.c` | **Uygulama (App)** | Sistemin giriş noktasıdır; test senaryolarını ve kullanıcı demosunu yönetir. |

---

## 📊 Algoritmik Analiz (Big-O)

Sıradan bir Dizi (Array) yerine Min-Heap kullanılmasının temel nedeni ölçeklenebilir performanstır:

| İşlem | Dizi (Sırasız) | Min-Heap (Projedeki) |
| :--- | :--- | :--- |
| **Ekleme (Push)** | $O(1)$ | $O(\log n)$ |
| **En Öncelikliyi Bulma** | $O(n)$ | $O(1)$ |
| **En Öncelikliyi Çekme (Pop)** | $O(n)$ | $O(\log n)$ |

> **Analiz:** 1 milyon istek barındıran bir sistemde dizi 1.000.000 işlem yaparken, Min-Heap yapısı sadece ~20 işlem ile en öncelikli isteği belirler ve ağacı yeniden dengeler.

---

## 🛠️ Kurulum ve Çalıştırma

### CLion Kullanarak:
1. Projeyi CLion ile açın.
2. `CMakeLists.txt` dosyasının otomatik olarak yüklenmesini bekleyin.
3. `Run` (Yeşil Oynat) butonuna basın.

### GCC (Terminal) Kullanarak:
```bash
gcc main.c scheduler.c -o api_scheduler
./api_scheduler
