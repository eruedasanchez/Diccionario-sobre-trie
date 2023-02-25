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
void string_map<T>::destruir(Nodo* r) {
    if (r != nullptr){
        for(int i = 0; i < 256; i++){
            Nodo* letra = r->siguientes[i];
            destruir(letra);
        }
        delete r;
    }
}

template <typename T>
string_map<T>::~string_map(){
    /* COMPLETAR */
    destruir(raiz);
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& a) {
    if (raiz == nullptr){
        /** Caso 1: El Trie se encuentra vacio, se inicializa un nuevo nodo y la raiz apunta a el **/
        Nodo* nodo_nuevo = new Nodo();
        raiz = nodo_nuevo;
    }
    /** Coso 2: El Trie NO se encuentra vacio. Se inserta la clave con su valor **/
    Nodo* nodo_actual = raiz;
    for (int i = 0; i < a.first.size(); i++) {
        for (int j = 0; j < 256; j++) {
            /** Se chequea si el i-esimo caracter al solicitar la funcion int (devuelve su codigo numerico asociado) coinicide con la posicion del vector siguientes. */
            if (j == int(a.first[i])) {
                if(nodo_actual->siguientes[j] == nullptr){
                    /** Si su nodo correspondiente apunta a nulo, se crea uno nuevo donde el puntero en la posicion j apunta al nodo creado para buscar la siguiente letra de la clave */
                    Nodo* aux = new Nodo();
                    nodo_actual->siguientes[j] = aux;
                }
                /** Se continuamos con la insercion de la siguiente letra de la clave y coloca a j en 256 asi se puede pasar a la siguiente letra */
                nodo_actual = nodo_actual->siguientes[j];
                j = 256;
            }
        }
    }
    _size++;
    nodo_actual->definicion = a.second;
    nodo_actual->status = true;
    dicc2.push_back(a);
}

template <typename T>
int string_map<T>::count(const string& key) const{
    /* COMPLETAR */
    Nodo* nodo_actual = raiz;
    if (_size == 0){
        /** Caso 1: El Trie se encuentra vacio */
        return 0;
    }

    /** Caso 2: El Trie NO se encuentra vacio. Entonces, se busca la clave key. */
    for(int i = 0; i < key.size();i++){
        for(int j = 0; j < 256; j++){
            if (j == int(key[i])){
                if (nodo_actual != nullptr){
                    nodo_actual = nodo_actual->siguientes[j];
                }
                j = 256;
            }
        }
    }
    /** Ya se recorrio toda la clave key. Ahora, se verifica si se encuentra en el Trie . */
    if (nodo_actual != nullptr && nodo_actual->status == true){
            return 1;
        } else {
            return 0;
        }
}

template <typename T>
const T& string_map<T>::at(const string& key) const {
    /* COMPLETAR */
    /** PRE: La clave key se encuentra definida en el Trie. */
    Nodo* nodo_actual = raiz;
    for(int i = 0; i < key.size();i++) {
        for(int j = 0; j < 256; j++) {
            if (j == int(key[i])) {
                nodo_actual = nodo_actual->siguientes[j];
            }
            j = 256;
        }
    }
    return nodo_actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& key) {
    /* COMPLETAR */
    Nodo* nodo_actual = raiz;
    for(int i = 0; i < key.size();i++) {
        for(int j = 0; j < 256; j++) {
            if (j == int(key[i])) {
                nodo_actual = nodo_actual->siguientes[j];
                j = 256;
            }
        }
    }
    return nodo_actual->definicion;
}


template <typename T>
T& string_map<T>::operator[](const string& clave){
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