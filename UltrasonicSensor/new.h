#ifndef NEW_H
  #define NEW_H
  // new
  void * operator new (size_t size) { return malloc (size); }
  // placement new
  void * operator new (size_t size, void * ptr) { return ptr; }
  // delete
  void operator delete (void * ptr) { free (ptr); }
#endif
