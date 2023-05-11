#include <iostream>
#include <string>
#include <stack>
using namespace std;

// Definisikan struktur data Tilang
struct Tilang {
    string kodeTilang;
    string platNomor;
    string jenisPelanggaran;
    string tempatPelanggaran;
    double jumlahDenda;
    bool statusPembayaran;

    Tilang() : jumlahDenda(0.0), statusPembayaran(false) {
        // Inisialisasi bidang-bidang lain jika perlu
    }
};

const int MAX_TILANG = 100; // Batasan maksimum jumlah tilang, bisa diubah sesuai keperluan
Tilang* dataTilang[MAX_TILANG]; // Array pointer untuk menyimpan tilang
int jumlahTilang = 0; // Jumlah tilang saat ini

// Node untuk linked list
struct Node {
    Tilang* data;
    Node* next;
};

// Implementasi Stack menggunakan linked list
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() {
        return top == nullptr;
    }

    void push(Tilang* data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    Tilang* pop() {
        if (isEmpty()) {
            return nullptr;
        }

        Node* temp = top;
        top = top->next;
        Tilang* data = temp->data;
        delete temp;
        return data;
    }
};

// Implementasi Queue menggunakan linked list
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Tilang* data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Tilang* dequeue() {
        if (isEmpty()) {
            return nullptr;
        }

        Node* temp = front;
        front = front->next;
        Tilang* data = temp->data;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return data;
    }
};

// Node untuk Binary Search Tree
struct BSTNode {
    Tilang* data;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(Tilang* tilang) : data(tilang), left(nullptr), right(nullptr) {}
};

// Deklarasi fungsi tampilkanData
void tampilkanData(const Tilang& data);

// Implementasi Binary Search Tree
class BST {
private:
    BSTNode* root;

public:
    BST() : root(nullptr) {}

    void insert(Tilang* data) {
        root = insertRecursive(root, data);
    }

    static BSTNode* insertRecursive(BSTNode* root, Tilang* data) {
        BSTNode* node = root;
        BSTNode* parent = nullptr;

        while (node != nullptr) {
            parent = node;

            if (data->kodeTilang < node->data->kodeTilang) {
                node = node->left;
            } else if (data->kodeTilang > node->data->kodeTilang) {
                node = node->right;
            } else {
                // Kalau misal kodeTilang udah di BST, bisa diatur sesuai kebutuhan               
                // Misalnya, lewati atau ganti data di node tersebut.
                return root;
            }
        }

        auto newNode = new BSTNode(data);

        if (parent == nullptr) {
            // BST kosong, jadikan newNode sebagai root
            return newNode;
        } else if (data->kodeTilang < parent->data->kodeTilang) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        return root;
    }

    void inorderTraversal() {
        inorderTraversalRecursive(root);
    }

    static void inorderTraversalRecursiveHelper(BSTNode* node) {
        stack<BSTNode*> stackNodes;
        BSTNode* current = node;

        while (current != nullptr || !stackNodes.empty()) {
            while (current != nullptr) {
                stackNodes.push(current);
                current = current->left;
            }

            current = stackNodes.top();
            stackNodes.pop();
            tampilkanData(*(current->data));

            current = current->right;
        }
    }

    static void inorderTraversalRecursive(BSTNode* node) {
        inorderTraversalRecursiveHelper(node);
    }
};

// Implementasi Graph menggunakan adjacency matrix
class Graph {
private:
    int maxVertices;
    int numVertices;
    Tilang** dataVertices;
    int** adjMatrix;

public:
    explicit Graph(int maxV) : maxVertices(maxV), numVertices(0) {
        dataVertices = new Tilang*[maxVertices];
        adjMatrix = new int*[maxVertices];

        for (int i = 0; i < maxVertices; i++) {
            dataVertices[i] = nullptr;
            adjMatrix[i] = new int[maxVertices];
            for (int j = 0; j < maxVertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < maxVertices; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
        delete[] dataVertices;
    }

    [[nodiscard]] bool isFull() const {
        return numVertices == maxVertices;
    }

    void addVertex(Tilang* data) {
        if (!isFull()) {
            dataVertices[numVertices] = data;
            numVertices++;
        } else {
            cout << "Graph penuh. Tidak dapat menambah vertex baru." << endl;
        }
    }

    void addEdge(int source, int destination) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjMatrix[source][destination] = 1;
            adjMatrix[destination][source] = 1;
        } else {
            cout << "Invalid vertex." << endl;
        }
    }

    void removeEdge(int source, int destination) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjMatrix[source][destination] = 0;
            adjMatrix[destination][source] = 0;
        } else {
            cout << "Invalid vertex." << endl;
        }
    }

    void display() {
        for (int i = 0; i < numVertices; i++) {
            cout << "Data Tilang pada Vertex " << i << ":" << endl;
            tampilkanData(*(dataVertices[i]));
            cout << endl;
        }

        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Fungsi untuk menampilkan data Tilang
void tampilkanData(const Tilang& data) {
    cout << "Kode Tilang: " << data.kodeTilang << endl;
    cout << "Plat Nomor: " << data.platNomor << endl;
    cout << "Jenis Pelanggaran: " << data.jenisPelanggaran << endl;
    cout << "Tempat Pelanggaran: " << data.tempatPelanggaran << endl;
    cout << "Jumlah Denda: " << data.jumlahDenda << endl;
    cout << "Status Pembayaran: " << (data.statusPembayaran ? "Lunas" : "Belum Lunas") << endl;
    cout << endl;
}
void tampilDataTilangBelumDibayar(Tilang** data, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!data[i]->statusPembayaran)
        {
            cout << "Data Tilang " << i + 1 << endl;
            cout << "Kode Tilang: " << data[i]->kodeTilang << endl;
            cout << "Plat Nomor: " << data[i]->platNomor << endl;
            cout << "Jenis Pelanggaran: " << data[i]->jenisPelanggaran << endl;
            cout << "Tempat Pelanggaran: " << data[i]->tempatPelanggaran << endl;
            cout << "Jumlah Denda: " << data[i]->jumlahDenda << endl;
            cout << "Status Pembayaran: " << (data[i]->statusPembayaran ? "Sudah Dibayar" : "Belum Dibayar") << endl;
            cout << endl;
        }
    }
}

void tampilDataTilangSudahDibayar(Tilang** data, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i]->statusPembayaran)
        {
            cout << "Data Tilang " << i + 1 << endl;
            cout << "Kode Tilang: " << data[i]->kodeTilang << endl;
            cout << "Plat Nomor: " << data[i]->platNomor << endl;
            cout << "Jenis Pelanggaran: " << data[i]->jenisPelanggaran << endl;
            cout << "Tempat Pelanggaran: " << data[i]->tempatPelanggaran << endl;
            cout << "Jumlah Denda: " << data[i]->jumlahDenda << endl;
            cout << "Status Pembayaran: " << (data[i]->statusPembayaran ? "Sudah Dibayar" : "Belum Dibayar") << endl;
            cout << endl;
        }
    }
}

void bubbleSort(Tilang** data, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (data[j]->kodeTilang > data[j + 1]->kodeTilang)
            {
                Tilang* temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

int binarySearch(Tilang** data, int left, int right, const string& target)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        int comparisonResult = data[mid]->kodeTilang.compare(target);

        if (comparisonResult == 0)
        {
            return mid;
        }

        if (comparisonResult > 0)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return -1;
}


void updatePaymentStatus(Tilang** data, int count, const string& kodeTilang)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i]->kodeTilang == kodeTilang)
        {
            data[i]->statusPembayaran = true;
            cout << "Status pembayaran untuk kode tilang " << kodeTilang << " berhasil diupdate." << endl;
            return;
        }
    }

    cout << "Kode tilang tidak ditemukan." << endl;
}

double calculateTotalDenda(Tilang** data, int count)
{
    double totalDenda = 0;
    for (int i = 0; i < count; i++)
    {
        totalDenda += data[i]->jumlahDenda;
    }
    return totalDenda;
}

int main() {
    char pilihan;
    bool selesai = false;

    Stack stack;
    Queue queue;
    BST bst;
    Graph graph(MAX_TILANG);

    while (!selesai) {
        // Tampilkan menu pilihan
        cout << "========================================" << endl;
        cout << "            APLIKASI CTILANG" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan Menu:" << endl;
        cout << "a. Tambah Data Tilang" << endl;
        cout << "b. Tampilkan Data Tilang" << endl;
        cout << "c. Tampilkan Data Tilang (Inorder Traversal)" << endl;
        cout << "d. Tampilkan Data Tilang (Graph)" << endl;
        cout << "e. Cek apakah Stack kosong" << endl;
        cout << "f. Cek apakah Queue Kosong" << endl;
        cout << "g. Tambahkan Edge pada Graph" << endl;
        cout << "h. Hapus Edge dari Graph" << endl;
        cout << "i. Edit data tilang" << endl;
        cout << "j. Hapus data tilang" << endl;
        cout << "k. Cari data tilang" << endl;
        cout << "l. Urutkan data tilang" << endl;
        cout << "m. Konfirmasi pembayaran tilang" << endl;
        cout << "n. Laporan uang pembayaran tilang" << endl;
        cout << "o. Tampilkan data tilang yang sudah dibayar" << endl;
        cout << "p. Tampilkan data tilang yang belum dibayar" << endl;
        cout << "q. Quit" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan pilihan (a, b, c, d, e): ";
        cin >> pilihan;
        cout << endl;
        switch (pilihan) {
            case 'a': {
                // Tambah Data Tilang
                if (jumlahTilang >= MAX_TILANG) {
                    cout << "Kapasitas tilang penuh. Tidak dapat menambahkan data tilang baru." << endl;
                } else {
                    auto tilangBaru = new Tilang; // Buat objek Tilang baru

                    cout << "Masukkan Kode Tilang: ";
                    cin >> tilangBaru->kodeTilang;
                    cout << "Masukkan Plat Nomor: ";
                    cin.ignore();
                    getline(cin, tilangBaru->platNomor);
                    cout << "Masukkan Jenis Pelanggaran: ";
                    getline(cin, tilangBaru->jenisPelanggaran);
                    cout << "Masukkan Tempat Pelanggaran: ";
                    getline(cin, tilangBaru->tempatPelanggaran);
                    cout << "Masukkan Jumlah Denda: ";
                    cin >> tilangBaru->jumlahDenda;
                    cout << "Masukkan Status Pembayaran (1: Lunas, 0: Belum Lunas): ";
                    cin >> tilangBaru->statusPembayaran;

                    dataTilang[jumlahTilang] = tilangBaru; // Menambahkan tilang baru ke dalam array
                    jumlahTilang++;

                    // Tambahkan ke Stack, Queue, BST, dan Graph
                    stack.push(tilangBaru);
                    queue.enqueue(tilangBaru);
                    bst.insert(tilangBaru);
                    graph.addVertex(tilangBaru);

                    cout << "Data tilang berhasil ditambahkan." << endl;
                }
                break;
            }
            case 'b': {
                // Tampilkan Data Tilang
                if (jumlahTilang == 0) {
                    cout << "Tidak ada data tilang yang tersedia." << endl;
                } else {
                    cout << "Data Tilang (Stack):" << endl;
                    while (!stack.isEmpty()) {
                        Tilang* data = stack.pop();
                        tampilkanData(*data);
                    }

                    cout << "Data Tilang (Queue):" << endl;
                    while (!queue.isEmpty()) {
                        Tilang* data = queue.dequeue();
                        tampilkanData(*data);
                    }
                }
                break;
            }
            case 'c': {
                // Tampilkan Data Tilang (Inorder Traversal BST)
                if (jumlahTilang == 0) {
                    cout << "Tidak ada data tilang yang tersedia." << endl;
                } else {
                    cout << "Data Tilang (Inorder Traversal BST):" << endl;
                    bst.inorderTraversal();
                }
                break;
            }
            case 'd': {
                // Tampilkan Data Tilang (Graph)
                if (jumlahTilang == 0) {
                    cout << "Tidak ada data tilang yang tersedia." << endl;
                } else {
                    cout << "Data Tilang (Graph):" << endl;
                    graph.display();
                }
                break;
            }
            case 'e': {
                // Cek apakah stack kosong
                if (stack.isEmpty()) {
                    cout << "Stack kosong." << endl;
                } else {
                    cout << "Stack tidak kosong." << endl;
                }
                break;
            }
            case 'f': {
                // Cek apakah queue kosong
                if (queue.isEmpty()) {
                    cout << "Queue kosong." << endl;
                } else {
                    cout << "Queue tidak kosong." << endl;
                }
                break;
            }
            case 'g': {
                // Tambahkan edge pada graph
                if (jumlahTilang < 2) {
                    cout << "Tidak cukup tilang untuk membuat edge." << endl;
                } else {
                    int source, destination;
                    cout << "Masukkan kode tilang sumber: ";
                    cin >> source;
                    cout << "Masukkan kode tilang tujuan: ";
                    cin >> destination;

                    graph.addEdge(source, destination);
                    cout << "Edge telah ditambahkan." << endl;
                }
                break;
            }
            case 'h': {
                // Hapus edge dari graph
                if (jumlahTilang < 2) {
                    cout << "Tidak cukup tilang untuk menghapus edge." << endl;
                } else {
                    int source, destination;
                    cout << "Masukkan kode tilang sumber: ";
                    cin >> source;
                    cout << "Masukkan kode tilang tujuan: ";
                    cin >> destination;

                    graph.removeEdge(source, destination);
                    cout << "Edge telah dihapus." << endl;
                }
                break;
            }
            case 'i':{
                if (jumlahTilang > 0)
                {
                    cout << endl << endl;
                    cout << "=== Update Data Pelanggaran Tilang ===" << endl;
                    cout << "Masukkan Kode Tilang yang akan diupdate: ";
                    string kodeTilangUpdate;
                    cin >> kodeTilangUpdate;
                    int indexUpdate = binarySearch(dataTilang, 0, jumlahTilang - 1, kodeTilangUpdate);
                    if (indexUpdate != -1)
                    {
                        cout << "Data Tilang saat ini:" << endl;
                        cout << "Kode Tilang: " << dataTilang[indexUpdate]->kodeTilang << endl;
                        cout << "Plat Nomor: " << dataTilang[indexUpdate]->platNomor << endl;
                        cout << "Jenis Pelanggaran: " << dataTilang[indexUpdate]->jenisPelanggaran << endl;
                        cout << "Tempat Pelanggaran: " << dataTilang[indexUpdate]->tempatPelanggaran << endl;
                        cout << "Jumlah Denda: " << dataTilang[indexUpdate]->jumlahDenda << endl;
                        cout << "Status Pembayaran: " << (dataTilang[indexUpdate]->statusPembayaran ? "Sudah Dibayar" : "Belum Dibayar") << endl;

                        cout << "Masukkan data baru:" << endl;
                        cout << "Masukkan Kode Tilang: ";
                        cin >> dataTilang[indexUpdate]->kodeTilang;
                        cout << "Masukkan Plat Nomor: ";
                        cin.ignore();
                        getline(cin, dataTilang[indexUpdate]->platNomor);
                        cout << "Masukkan Jenis Pelanggaran: ";
                        getline(cin, dataTilang[indexUpdate]->jenisPelanggaran);
                        cout << "Masukkan Tempat Pelanggaran: ";
                        getline(cin, dataTilang[indexUpdate]->tempatPelanggaran);
                        cout << "Masukkan Jumlah Denda: ";
                        cin >> dataTilang[indexUpdate]->jumlahDenda;
                        cout << "Masukkan Status Pembayaran (1 = Sudah Dibayar, 0 = Belum Dibayar): ";
                        cin >> dataTilang[indexUpdate]->statusPembayaran;

                        cout << "Data Tilang berhasil diupdate." << endl;
                        cout << endl << endl;
                    }
                    else
                    {
                        cout << "Kode Tilang tidak ditemukan." << endl;
                        cout << endl << endl;
                    }
                }
                else
                {
                    cout << "Tidak ada data tilang yang tersedia." << endl;
                    cout << endl << endl;
                }
                break;
            }
            case 'j' : {
                if (jumlahTilang > 0)
                {
                    cout << endl << endl;
                    cout << "=== Hapus Data Pelanggaran Tilang ===" << endl;
                    cout << "Masukkan Kode Tilang yang akan dihapus: ";
                    string kodeTilangHapus;
                    cin >> kodeTilangHapus;
                    int indexHapus = binarySearch(dataTilang, 0, jumlahTilang - 1, kodeTilangHapus);
                    if (indexHapus != -1)
                    {
                        for (int i = indexHapus; i < jumlahTilang - 1; i++)
                        {
                            dataTilang[i] = dataTilang[i + 1];
                        }
                        jumlahTilang--;
                        cout << "Data Tilang berhasil dihapus." << endl;
                        cout << endl << endl;
                    }
                    else
                    {
                        cout << "Kode Tilang tidak ditemukan." << endl;
                        cout << endl << endl;
                    }
                }
                else
                {
                    cout << "Tidak ada data tilang yang tersedia." << endl;
                    cout << endl << endl;
                }
                break;
            }
            case 'k' : {
                if (jumlahTilang > 0)
                {
                    cout << endl << endl;
                    cout << "=== Cari Data Tilang Berdasarkan Kode Tilang ===" << endl;
                    cout << "Masukkan Kode Tilang yang akan dicari: ";
                    string kodeTilangCari;
                    cin >> kodeTilangCari;
                    int indexCari = binarySearch(dataTilang, 0, jumlahTilang - 1, kodeTilangCari);
                    if (indexCari != -1)
                    {
                        cout << "Data Tilang ditemukan:" << endl;
                        cout << "Kode Tilang: " << dataTilang[indexCari]->kodeTilang << endl;
                        cout << "Plat Nomor: " << dataTilang[indexCari]->platNomor << endl;
                        cout << "Jenis Pelanggaran: " << dataTilang[indexCari]->jenisPelanggaran << endl;
                        cout << "Tempat Pelanggaran: " << dataTilang[indexCari]->tempatPelanggaran << endl;
                        cout << "Jumlah Denda: " << dataTilang[indexCari]->jumlahDenda << endl;
                        cout << "Status Pembayaran: " << (dataTilang[indexCari]->statusPembayaran ? "Sudah Dibayar" : "Belum Dibayar") << endl;
                        cout << endl << endl;
                    }
                    else
                    {
                        cout << "Kode Tilang tidak ditemukan." << endl;
                        cout << endl << endl;
                    }
                }
                else
                {
                    cout << "Tidak ada data tilang yang tersedia." << endl;
                    cout << endl << endl;
                }
                break;
            }
            case 'l' :{
                cout << endl << endl;
                cout << "=== Urutkan Data Tilang ===" << endl;
                bubbleSort(dataTilang, jumlahTilang);
                cout << "Data Tilang berhasil diurutkan." << endl;
                cout << endl << endl;
                break;
            }
            case 'm' :{
                if (jumlahTilang > 0)
                {
                    cout << endl << endl;
                    cout << "=== Konfirmasi Pembayaran Tilang ===" << endl;
                    cout << "Masukkan Kode Tilang yang akan dikonfirmasi pembayarannya: ";
                    string kodeTilangBayar;
                    cin >> kodeTilangBayar;
                    updatePaymentStatus(dataTilang, jumlahTilang, kodeTilangBayar);
                    cout << endl << endl;
                }
                else
                {
                    cout << "Tidak ada data tilang yang tersedia." << endl;
                    cout << endl << endl;
                }
                break;
            }
            case 'n' :{
                cout << endl << endl;
                cout << "=== Laporan Uang Pembayaran Tilang ===" << endl;
                double totalDenda = calculateTotalDenda(dataTilang, jumlahTilang);
                cout << "Total Uang Pembayaran Tilang: " << totalDenda << endl;
                cout << endl << endl;
                break;
            }
            case 'o' :{
                cout << endl << endl;
                cout << "=== Data Tilang Sudah Dibayar ===" << endl;
                tampilDataTilangSudahDibayar(dataTilang, jumlahTilang);
                cout << endl << endl;
                break;
            }
            case 'p' :{
                cout << endl << endl;
                cout << "=== Data Tilang Belum Dibayar ===" << endl;
                tampilDataTilangBelumDibayar(dataTilang, jumlahTilang);
                cout << endl << endl;
                break;
            }
            case 'q': {
                // Keluar
                selesai = true;
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan pilih menu yang tersedia." << endl;
        }
        cout << endl;
    }

    // Menghapus memori yang dialokasikan untuk setiap objek Tilang
    for (int i = 0; i < jumlahTilang; i++) {
        delete dataTilang[i];
    }

    return 0;
}


