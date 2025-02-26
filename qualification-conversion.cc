int main() {
  int x = 55;
  const char c = 'c';
  char *pc = new char('g');
  const char **pcc = &pc;
  *pcc = &c; // modifies a const object
  *pc = 'C';
}
