// #define __SOL__
#define __TESTS__

#ifdef __SOL__
#include "sol01.cpp"
#else
#include "esame01.cpp"
#endif

bool checkfiles(const char* filename1, const char* filename2);

int main() {
  // init non testato
  int voto_init = 0;
  RecordSet rs_ = init();
  if (rs_.size == 0) voto_init += 2;
  cout << "Voto per init: " << voto_init << endl;

  // drop non testato
  int voto_drop = 0;
  drop(rs_);
  if (rs_.size == 0) voto_drop += 1;
  cout << "Voto per drop: " << voto_drop << endl;

  // tests per insert
  int voto_insert = 0;
  RecordSet rs = init();
  if (insert(rs, 0, "Pippo", 10) == 0 && insert(rs, 6, "Pluto", 20) == 1)
    voto_insert += 1;
  if (insert(rs, 6, "Paperino", 30) == -1) voto_insert += 1;
  if (insert(rs, 2, "Minni", 30) == 2 && insert(rs, 3, "Minni", 40) == 3)
    voto_insert += 1;
  if (insert(rs, 4, "Paperone", 60) == 4) voto_insert += 2;
  // hacky delete for testing
  if (rs.size >= 5) rs.records[4].id = -1;
  if (insert(rs, 4, "Paperone", 50) == 4) voto_insert += 1;
  cout << "Voto per insert: " << voto_insert << endl;

  // tests per rcount
  int voto_rcount = 0;
  if (rcount(rs) == 5) voto_rcount += 1;
  cout << "Voto per rcount: " << voto_rcount << endl;

  // tests per vsum
  int voto_vsum = 0;
  if (vsum(rs, "Pippo") == 10) voto_vsum += 1;
  if (vsum(rs, "Minni") == 70) voto_vsum += 1;
  cout << "Voto per vsum: " << voto_vsum << endl;

  // tests per search
  int voto_search = 0;
  if (search(rs, 2) == 2) voto_search += 1;
  if (search(rs, 10) == -1) voto_search += 1;
  cout << "Voto per search: " << voto_search << endl;

  // tests per find
  int voto_find = 0;
  if (find(rs, "Pippo", 0) == 0) voto_find += 1;
  if (find(rs, "Minni", 0) == 2) voto_find += 1;
  if (find(rs, "Minni", 3) == 3) voto_find += 1;
  cout << "Voto per find: " << voto_find << endl;

  // tests per update
  int voto_update = 0;
  if (update(rs, 0, 1) == 0 && rs.records[0].value == 1) voto_update += 1;
  if (update(rs, 5, 0) == -1) voto_update += 1;
  cout << "Voto per update: " << voto_update << endl;

  // tests per remove
  int voto_remove = 0;
  if (remove(rs, 0) == 0) voto_remove += 1;
  if (remove(rs, 10) == -1) voto_remove += 1;
  cout << "Voto per remove: " << voto_remove << endl;

  // tests per erase
  int voto_erase = 0;
  if (erase(rs, "Pluto") == 1 && rs.records[1].id == -1) voto_erase += 1;
  if (erase(rs, "Minni") == 2 && rs.records[2].id == -1 &&
      rs.records[3].id == -1)
    voto_erase += 2;
  cout << "Voto per erase: " << voto_erase << endl;

  // tests per load and save
  int voto_load = 0;
  RecordSet rsf = load("load01.txt");
  if (rsf.size == 4) voto_load += 3;
  if (rsf.size == 4) {
    if (rsf.records[0].value == 1) voto_load += 1;
    if (rsf.records[2].id == 4) voto_load += 1;
  }
  cout << "Voto per load: " << voto_load << endl;

  int voto_save = 0;
  if (save(rsf, "save01.txt") == 0) voto_save += 1;
  save(rsf, "save01.txt");
  if (checkfiles("load01.txt", "save01.txt")) voto_save += 3;
  cout << "Voto per save: " << voto_save << endl;

  // Voto finale
  int voto = voto_init + voto_drop + voto_insert + voto_rcount + voto_vsum +
             voto_search + voto_find + voto_update + voto_remove + voto_erase +
             voto_load + voto_save;
  cout << "Voto: " << voto << endl;
  return 0;
}

#include <string>

bool checkfiles(const char* filename1, const char* filename2) {
  ifstream ifs1(filename1);
  ifstream ifs2(filename2);
  if (!ifs1 || !ifs2) return false;
  string s1, s2;
  while (ifs1 >> s1) {
    if (!(ifs2 >> s2)) return false;
    if (s1 != s2) return false;
  }
  return true;
}
