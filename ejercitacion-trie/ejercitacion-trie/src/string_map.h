#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <vector>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T>& a);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string& key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string& key);

private:

    struct Nodo {
        /** Cada nodo esta representado por un vector de punteros a nodos donde cada puntero apunta a un vector de 256 punteros
         * donde cada posicion representa un puntero a un caracter del codigo ASCII */
        vector<Nodo*> siguientes;

        /** Puntero al significado de la clave del diccionario */
        T definicion;

        /** Indica si el nodo tiene definida una clave */
        bool status;

        /** Inicializacion de los nodos de la estructura */
        Nodo() : siguientes(256, nullptr), definicion(), status(false) {}
        Nodo(T def) : siguientes(256, nullptr), definicion(def), status(true) {}

    };

    /** Puntero a la raiz del Trie */
    Nodo* raiz;

    /** Indica la cantidad de claves definidas actualmente en el diccionario Trie */
    int _size;

    /** DESTRUCTOR AUXILIAR **/
    void destruir(Nodo* r);

    vector<pair<string,T>> dicc2;
    vector<pair<string,T>> dicc();

    /** Indica si un nodo tiene hijos **/
    bool hijos(Nodo const* r);

    /** Indica si un nodo es hijo **/
    bool hijo(Nodo const* r);

};

#include "string_map.hpp"

#endif // STRING_MAP_H_
