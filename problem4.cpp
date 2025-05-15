#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Patient
{
  string name;
  int severity;
  int arrival_time;

  bool operator>(const Patient &other) const
  {
    if (severity == other.severity)
      return arrival_time < other.arrival_time;
    return severity > other.severity;
  }

  string toString() const
  {
    return name + " (Severity: " + to_string(severity) + ", Arrival: " + to_string(arrival_time) + ")";
  }
};

class MaxHeap
{
private:
  vector<Patient> heap;

  int parent(int i) { return (i - 1) / 2; }
  int left(int i) { return 2 * i + 1; }
  int right(int i) { return 2 * i + 2; }

  void heapifyUp(int i)
  {
    while (i > 0 && heap[i] > heap[parent(i)])
    {
      swap(heap[i], heap[parent(i)]);
      i = parent(i);
    }
  }

  void heapifyDown(int i)
  {
    int size = heap.size();
    while (true)
    {
      int largest = i;
      int l = left(i), r = right(i);

      if (l < size && heap[l] > heap[largest])
        largest = l;
      if (r < size && heap[r] > heap[largest])
        largest = r;

      if (largest != i)
      {
        swap(heap[i], heap[largest]);
        i = largest;
      }
      else
      {
        break;
      }
    }
  }

public:
  void insert(const Patient &p)
  {
    heap.push_back(p);
    heapifyUp(heap.size() - 1);
  }

  Patient extract_max()
  {
    if (heap.empty())
      return {"None", -1, -1};

    Patient maxPatient = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
      heapifyDown(0);

    return maxPatient;
  }

  Patient peek() const
  {
    if (heap.empty())
      return {"None", -1, -1};
    return heap[0];
  }

  void print_heap() const
  {
    for (const auto &p : heap)
      cout << p.name << " ";
    cout << endl;
  }

  bool isEmpty() const
  {
    return heap.empty();
  }
};

int main()
{
  MaxHeap er_queue;
  ifstream infile("input.txt");

  if (!infile)
  {
    cerr << "Error: Could not open input.txt\n";
    return 1;
  }

  string name;
  int severity, arrival_time;
  cout << "Heap After Insertions:\n";

  while (infile >> name >> severity >> arrival_time)
  {
    Patient p{name, severity, arrival_time};
    cout << "Inserting: " << p.name << endl;
    er_queue.insert(p);
    cout << "Heap: ";
    er_queue.print_heap();
    cout << endl;
  }

  infile.close();

  cout << "\nTreatment Order:\n";
  while (!er_queue.isEmpty())
  {
    Patient treated = er_queue.extract_max();
    cout << "Treating: " << treated.name << endl;
  }

  return 0;
}
