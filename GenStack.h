#include <iostream>
#include <exception>

template <class T>
class GenStack{
public:
  GenStack(); //default Constructor
  ~GenStack();//deconstructor
  void Push(const T& data);
  T pop();
  T& top();
  const T& peek() const;
  bool isEmpty() const;
  int getSize() const;

private:
  T* myArray;
  int mAlloc;
  int mtop;
};

template <class T>
GenStack<T>::GenStack(){
  myArray = new T[1];
  int mAlloc = 1;
  int mtop = -1;
}
template <class T>
GenStack<T>::~GenStack(){
  delete[] myArray;
  myArray = nullptr;
  mAlloc = 0;
  mtop = -1;
}
template <class T>
void GenStack<T>::Push(const T& data){
  if(++mtop == mAlloc){
    //Capicityhas been reached. So double Capicity before push new item
    T* new_array = new T[mAlloc * 2];
    for(int i = 0; i < mAlloc; ++i){
      new_array[i] = myArray[i];
    }
    delete[] myArray;
    myArray = new_array;
    new_array = nullptr;
    mAlloc *= 2;
  }
  myArray[++mtop] = data;
}
template <class T>
T GenStack<T>::pop(){
  if(isEmpty()){
    //throw std::exception("Pop called an empty stack");
    throw std::exception();
  }
  --mtop;
}
template <class T>
T& GenStack<T>::top(){
  if(isEmpty()){
    throw std::exception();
  }
  return myArray[mtop];
}
template <class T>
const T& GenStack<T>::peek() const{
  if(isEmpty()){
    throw std::exception();
  }
  return myArray[mtop];
}
template <class T>
bool GenStack<T>::isEmpty() const{
  return (mtop == -1);
}
template <class T>
int GenStack<T>::getSize() const{
  return mtop + 1;
}
