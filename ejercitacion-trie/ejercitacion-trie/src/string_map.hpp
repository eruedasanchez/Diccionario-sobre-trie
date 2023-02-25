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
vector<pair<string, T>> string_map<T>::dicc() {
    return dicc2;
}

template <typename T>
string_map<T>::~string_map(){
    /* COMPLETAR */
    destruir(raiz);
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
                /** Se continua con la insercion de la siguiente letra de la clave y coloca a j en 256 asi se puede pasar a la siguiente letra */
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
    if (nodo_actual != nullptr){
        if (nodo_actual->status == true){
            return 1;
        } else {
            return 0;
        }
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
                j = 256;
            }
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
void string_map<T>::erase(const string& key) {
    /* COMPLETAR */
    /** Se crea un diccionario auxiliar donde se van guardando todas las claves distintas a key (la que se quiere borrar) */
    vector<pair<string,T>> diccaux;
    for(int i = 0; i < dicc2.size(); i++) {
        if(dicc2[i].first != key)
            diccaux.push_back(dicc2[i]);
    }
    /** Ahora, diccDos vuelve a ser el diccionario original pero sin la clave a eliminar con su respectivo significado. */
    dicc2 = diccaux;
    Nodo* nodo_actual = raiz;
    Nodo* nodo_aux = raiz;
    int last = 0;
    for(int i = 0; i < key.size();i++) {
        for(int j = 0; j < 256; j++) {
            if(hijos(nodo_actual) || nodo_actual->status || nodo_actual == raiz) {
                nodo_aux = nodo_actual;
                if (j == int(key[i])){
                    last = j;
                }
            }
            if (j == int(key[i])) {
                nodo_actual = nodo_actual->siguientes[j];
                j = 256;
            }
        }
    }
    _size--;
    nodo_actual->status = false;
    Nodo* nodo_borrar = nodo_aux->siguientes[last];
    if (!hijo(nodo_actual)) {
        destruir(nodo_borrar);
        nodo_aux->siguientes[last] = nullptr;
    }
}

template <typename T>
bool string_map<T>::hijos(Nodo const* r) {
    int acum = 0;
    for (int i = 0; i < 256; i++) {
        if (r->siguientes[i] != nullptr){
            acum++;
        }
    }
    if (acum > 1){
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool string_map<T>::hijo(Nodo const* r) {
    for (int i = 0; i < 256; i++) {
        if (r->siguientes[i] != nullptr){
            return true;
        }
    }
    return false;
}

template <typename T>
int string_map<T>::size() const{
    /* COMPLETAR */
    return _size;

}

template <typename T>
bool string_map<T>::empty() const{
    /* COMPLETAR */
    return _size == 0;
}

template <typename T>
T& string_map<T>::operator[](const string& key){
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










