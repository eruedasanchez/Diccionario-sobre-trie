template <typename T>
string_map<T>::string_map(): raiz(nullptr), _size(0) {
    /* COMPLETAR */
    /** Constructor. Inicializacion de un Trie vacio */
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar; // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.
}

template <typename T>
vector<pair<string, T>> string_map<T>::dicc() {
    return dicc2;
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    /* COMPLETAR */
    destruir(raiz);
    _size = 0;
    for(int i = 0; i < d.dicc2.size(); i++) {
        insert(d.dicc2[i]);
        _size++;
    }
}

template <typename T>
string_map<T>::~string_map(){
    /* COMPLETAR */
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    /* COMPLETAR */
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    /* COMPLETAR */
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    /* COMPLETAR */
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    /* COMPLETAR */
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    /* COMPLETAR */
}

template <typename T>
int string_map<T>::size() const{
    /* COMPLETAR */
}

template <typename T>
bool string_map<T>::empty() const{
    /* COMPLETAR */
}