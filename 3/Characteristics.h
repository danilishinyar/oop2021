#ifndef LAB3_REFACTORED_CHARACTERISTICS_H
#define LAB3_REFACTORED_CHARACTERISTICS_H
#include<iostream>
#include <vector>
#include <string>
#include <fstream>


/*!
 * @brief Структура элемента таблицы Characteristics
 * @tparam U
 * @tparam T
 */
template <class U, class T>
struct Cell{
    U title;
    T value;
};


/*!
 * @brief Класс итератор
 * @tparam U тип данных ключа
 * @tparam T тип данных значения
 */
template <class U, class T>
class Iterator{
private:
    Cell<U, T>* cur;/// Текущий элемент
public:
    Iterator(): cur(nullptr){ };/// Конструктор по умолчанию
    /*!
     * @brief Конструктор
     * @param ob указатель на элемент таблицы
     */
    explicit Iterator(Cell<U, T>* ob): cur(ob){ };
    /*!
     * @brief Оператор разыменования указателя
     * @return ссылку на элемент таблицы
     */
    Cell<U, T>& operator *();
    /*!
     * @brief Оператор префиксного инкремента
     */
    Iterator& operator ++();
    /*!
    * @brief Оператор постфиксного инкремента
    */
    Iterator& operator ++(int);
    /*!
    * @brief Оператор равенства
    */
    int operator ==(const Iterator& ptr) const;
    /*!
    * @brief Оператор неравенства
    */
    int operator !=(const Iterator& ptr) const;
};


/*!
 * @brief Таблица характеристик
 * @tparam U тип данных ключа
 * @tparam T тип данных значения
 */
template <class U, class T>
class Characteristics{
private:
    Cell<U, T>* tb;/// Массив указателей на Cell
    int size; /// Размер таблицы
    friend class Iterator<U, T>; /// Класс итератор
public:
    /*!
     * @return Начальный эелемент таблицы
     */
    Iterator<U, T> begin();
    /*!
     * @return Конечный элемент таблицы
     */
    Iterator<U, T> end();
    /*!
     * @brief Констурктор по умолчанию (создает пустую таблицу)
     */
    Characteristics(): tb(nullptr), size(0){};
    /*!
     * @brief Копирующий констуктор
     * @param a оъект, который нужно скопировать
     */
    Characteristics(const Characteristics& a);
    /*!
     * @brief Перемещающий конструктор
     * @param a оъект, который нужно переместить
     */
    Characteristics(Characteristics&& a) noexcept;
    /*!
     * @brief Конструктор
     * @param filename название файла, из которого нужно выгрузить таблицу
     */
    explicit Characteristics(const std::string& filename);
    /*!
     * @brief Деструктор
     */
    ~Characteristics(){
        if(this->tb != nullptr)
            delete[] tb;
    }
    /*!
     * @brief Получение массива указателей на элементы таблицы
     * @return указатель на начало массива
     */
    [[nodiscard]] Cell<U, T>* get() const;
    /*!
     * @brief Получение текущего размера таблицы
     * @return размер таблицы
     */
    [[nodiscard]] int get_size() const;
    /*!
     * @brief Получение значения по ключу
     * @param title ключ
     * @return значение
     */
    [[nodiscard]] T get_val(const std::string& title);
    /*!
     * @brief Изменение значения по ключу
     * @param title ключ
     * @param value новое значение
     */
    void set(const std::string& title, T value);
    /*!
     * @brief Перегруженный опретор присваивания перемещением
     * @param a объект,который нужно переместить
     */
    Characteristics& operator=(Characteristics &&a) noexcept;
    /*!
     * @brief Перегруженный опретор присваивания копированием
     * @param a объект,который нужно скопировать
     */
    Characteristics& operator=(const Characteristics &a);
    Characteristics operator+( Characteristics &a);
    Characteristics operator-(Characteristics &a);
};



template <class U, class T>
Characteristics<U, T>::Characteristics(const std::string& filename) {
    std::ifstream file;
    file.open("/Users/danilishinyar/OOP/lab3_refactored/conf/" + filename + ".txt");
    std::string line;
    int quota = 5;
    this->size = 0;
    this->tb = new Cell<U, T>[quota];
    if(file.is_open()){
        T tmp_value;
        U tmp_key;
        int b = 1;
        int i = 0;
        Cell<U, T> tmp_cell;
        while(file >> tmp_key >> tmp_value){
            this->size++;
            if(this->size > quota * b){
                b++;
                auto* tmp = new Cell<U, T>[b * quota];
                memcpy(tmp, this->tb, sizeof(Cell<U, T>) * quota * (b - 1));
                delete[] this->tb;
                this->tb = tmp;
            }
            tmp_cell.title = tmp_key;
            tmp_cell.value = tmp_value;
            this->tb[i] = tmp_cell;
            i++;
        }
        file.close();
    }
    else
        throw std::runtime_error("unable to open conf file");
}


template <class U, class T>
Characteristics<U, T>::Characteristics(const Characteristics<U, T> &a) {
    size = a.size;
    tb = new Cell<U, T>[(a.size / 5 + 1) * 5];
    memcpy(tb, a.tb, sizeof(Cell<U, T>) * a.size);
}

template <class U, class T>
Characteristics<U, T>::Characteristics(Characteristics<U, T> &&a) noexcept{
    size = a.size;
    tb = a.tb;
    a.tb = nullptr;
}

template <class U, class T>
Cell<U, T>* Characteristics<U, T>::get() const {
    return this->tb;
}

template <class U, class T>
int Characteristics<U, T>::get_size() const {
    return this->size;
}

template <class U, class T>
Iterator<U, T> Characteristics<U, T>::begin(){
    return Iterator<U, T>(this->tb);
}

template <class U, class T>
Iterator<U, T> Characteristics<U, T>::end(){
    return Iterator<U, T>(this->tb + this->size);
}

template <class U, class T>
Cell<U, T>& Iterator<U, T>::operator*() {
    return *cur;
}

template <class U, class T>
Iterator<U, T>& Iterator<U, T>::operator ++(){
    this->cur++;
    return *this;
}

template <class U, class T>
Iterator<U, T>& Iterator<U, T>::operator ++(int){
    Iterator<U, T> tmp;
    tmp.cur = this->cur;
    tmp.cur++;
    return tmp;
}

template <class U, class T>
int Iterator<U, T>::operator ==(const Iterator<U, T>& ptr) const{
    return ptr.cur == this->cur;
}

template <class U, class T>
int Iterator<U, T>::operator !=(const Iterator<U, T>& ptr) const{
    return ptr.cur != this->cur;
}

template <class U, class T>
void Characteristics<U, T>::set(const std::string& title, T value){
    Iterator<U, T> it;
    for(it = this->begin(); it != this->end();++it)
        if(title == (*it).title)
            (*it).value = value;
}

template <class U, class T>
T Characteristics<U, T>::get_val(const std::string& title) {
    Iterator<U, T> it;
    for(it = this->begin(); it != this->end();++it)
        if(title == (*it).title)
            return((*it).value);
    throw std::runtime_error("invalid title in table");
}

template <class U, class T>
Characteristics<U, T>& Characteristics<U, T>::operator=(Characteristics<U, T> &&a) noexcept{
    if(this == &a)
        return *this;
    delete[] tb;
    size = a.size;
    tb = a.tb;
    a.size = 0;
    a.tb = nullptr;
    return *this;
}

template <class U, class T>
Characteristics<U, T>& Characteristics<U, T>::operator=(const Characteristics<U, T> &a) {
    if(this == &a)
        return *this;
    size = a.size;
    delete[] tb;
    tb = new Cell<U, T>[a.size];
    memcpy(tb, a.tb, a.size * sizeof(Cell<U, T>));
    return *this;
}


template <class U, class T>
Characteristics<U, T> Characteristics<U, T>::operator+(Characteristics<U, T> &a){
    for(Iterator<U, T> it = this->begin(); it != this->end();++it){
        for(Iterator<U, T> it1 = a.begin(); it1 != a.end();++it1){
            if((*it).title == (*it1).title)
                (*it).value += (*it1).value;
        }
    }
    return *this;
};

template <class U, class T>
Characteristics<U, T> Characteristics<U, T>::operator-(Characteristics<U, T> &a){
    for(Iterator<U, T> it = this->begin(); it != this->end();++it){
        for(Iterator<U, T> it1 = a.begin(); it1 != a.end();++it1){
            if((*it).title == (*it1).title)
                (*it).value -= (*it1).value;
        }
    }
    return *this;
};

#endif //LAB3_REFACTORED_CHARACTERISTICS_H
