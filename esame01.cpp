// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  int id;
  char name[128];
  int value;
};

struct RecordSet {
  Record* records;
  int size;
  int capacity;
};

// FUNZIONI DI AIUTO -----------------------------------------------------------

void print(const RecordSet& rs) {
  cout << "RecordSet: " << rs.size << "/" << rs.capacity << endl;
  for (int idx = 0; idx < rs.size; idx++) {
    cout << "  " << rs.records[idx].id << " " << rs.records[idx].name << " "
         << rs.records[idx].value << endl;
  }
}

// FUNZIONI --------------------------------------------------------------------

RecordSet init() {
  // DA IMPLEMENTARE
  RecordSet rs;
  rs.records = nullptr;
  rs.size = 0;
  rs.capacity = 0;
  return rs;
}

void drop(RecordSet& rs) {
  // DA IMPLEMENTARE
  if (rs.records != nullptr) {
    delete[] rs.records;
    rs.records = nullptr;
    rs.size = 0;
    rs.capacity = 0;
  }
}

int search(const RecordSet& rs, int id);
int insert(RecordSet& rs, int id, const char* name, int value) {
  // DA IMPLEMENTARE
  if (search(rs, id) != -1) {
    return -1;
    
  }

  if (rs.records != nullptr) {
    for (int i = 0; i < rs.size; i++) {
      if (rs.records[i].id == -1) {
          rs.records[i].id = id;
          strcpy(rs.records[i].name, name);
          rs.records[i].value = value;
          return i;
      }
    }

  }

  if (rs.size == rs.capacity) {
  	
    Record* tmp = new Record[ (rs.capacity == 0) ? 2 : rs.capacity * 2];
    for (int i = 0; i < rs.size; i++) {
      tmp[i] = rs.records[i];
    }
    delete[] rs.records;
    rs.records = tmp;
    rs.capacity = (rs.capacity == 0) ? 1 : rs.capacity;
    rs.capacity *= 2;
  }
  rs.records[rs.size].id = id;
  strcpy(rs.records[rs.size].name, name);
  rs.records[rs.size].value = value;
  rs.size += 1;
  return rs.size-1;
}

int rcount(const RecordSet& rs) {
  // DA IMPLEMENTARE
  int count = 0;
  for (int i = 0; i < rs.size; i++) {
    if (rs.records[i].id != -1) {
      count += 1;
    }
  }
  return count;
}

int vsum(const RecordSet& rs, const char* name) {
  // DA IMPLEMENTARE
  int sum = 0;
  for (int i = 0; i < rs.size; i++) {
    if (strcmp(rs.records[i].name, name) == 0) {
      sum += rs.records[i].value;
    }
  }
  return sum;
}

int search(const RecordSet& rs, int id) {
  // DA IMPLEMENTARE
  for (int i = 0; i < rs.size; i++) {
    if (rs.records[i].id == id) {
      return i;
    }
  }
  return -1;
}

int find(const RecordSet& rs, const char* name, int start) {
  // DA IMPLEMENTARE
  for (int i = start; i < rs.size; i++) {
    if (strcmp(rs.records[i].name, name) == 0) {

      return i;
    }
  }
  return -1;
}

int update(RecordSet& rs, int id, int value) {
  // DA IMPLEMENTARE
  int pos = search(rs, id);
  if (pos == -1) {
    return -1;
  }
  rs.records[pos].value = value;
  return pos;
}

int remove(RecordSet& rs, int id) {
  // DA IMPLEMENTARE
  int pos = search(rs, id);
  if (pos == -1) {
    return -1;
  }

  rs.records[pos].id = -1;
  strcpy(rs.records[pos].name, " ");
  rs.records[pos].value = 0;

  return pos;
}

int erase(RecordSet& rs, const char* name) {
  // DA IMPLEMENTARE
  int first_pos = -1, pos = -1;
  do {

    pos = find(rs, name, (pos != -1 && (pos + 1) < rs.size ) ? pos + 1 : 0 );
    first_pos = (pos != -1 && first_pos == -1) ? pos : first_pos;
    (pos != -1 ) ? remove(rs, rs.records[pos].id) : 0;

  } while (pos != -1 );

  return first_pos;
}

RecordSet load(const char* filename) {
  // DA IMPLEMENTARE
  ifstream ifs(filename);
  if (!ifs) {
    return init();
  }

  RecordSet rs = init();
  
  while (ifs) {
    if (rs.size == rs.capacity) {
      
      Record* tmp = new Record[ (rs.capacity == 0) ? 2 : rs.capacity * 2];
      if (rs.records != nullptr) {
      for (int i = 0; i < rs.size; i++) {
        tmp[i] = rs.records[i];
      }
      }

      delete[] rs.records;
      rs.records = tmp;
      rs.capacity = (rs.capacity == 0) ? 1 : rs.capacity;
      rs.capacity *= 2;
    }
    ifs >> rs.records[rs.size].id >> rs.records[rs.size].name >> rs.records[rs.size].value;
    rs.size += 1;

  }
  rs.size --;
  return rs;

}

int save(const RecordSet& rs, const char* filename) {
  // DA IMPLEMENTARE
  ofstream ofs(filename);
  if (!ofs) {
    return -1;
  }

  for (int i = 0; i < rs.size; i++) {
    if (rs.records[i].id != -1) {
      ofs << rs.records[i].id << " " << rs.records[i].name << " " << rs.records[i].value << endl;
    }

  }

  return 0;

}

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
