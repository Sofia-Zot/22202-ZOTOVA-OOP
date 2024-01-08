#ifndef TASK1_BITARRAY_H
#define TASK1_BITARRAY_H

#include <cmath>
#include <iostream>
#include <algorithm>

template<typename blockType>
class BitArray {
private:

    typedef unsigned char byte;

    static const int bytesPerBlock = sizeof(blockType);//байт на блок
    static const int bitsPerBlock =  bytesPerBlock * 8;//бит на блок

    blockType *array;//основной массив

    int capacityInBytes;//размер массива в байтах
    int capacityInBites;//размер массива в битах
    int currSizeInBites;//использовано бит

    [[nodiscard]] int lastUnusedByteInd() const;//последний неиспользованный байт

    void reallocateArray(int numberOfBits);//перемещение массива в памяти для изменения размера на numBits и объема, если numBits < 0

    class Bit { // методы для статичного массива
    private:
        BitArray<blockType> *bitArray; //оригинальный битовый массив

        int index;

    public:
        bool value;

        Bit(BitArray<blockType> *bitArray, int i); //создание массива

        Bit(const Bit &source); //копирование из источника

        Bit &operator=(bool v);//присваивание значения указанному биту

        Bit &operator=(const Bit &source);//присваивание объекта

        explicit operator bool() {
            return this->value;
        }
    };

public:

    BitArray();//создание нового пустого массива
    ~BitArray();//удаление массива

    explicit BitArray(int numberOfBits, blockType value = 0);// создает чистый массив длинной nOb
    BitArray(const BitArray &source); //копирует массив

    void swap(BitArray &source);//меняет местами два массива, если они одного размера

    [[nodiscard]] bool get(int ind) const {//для работы с битами
        if (ind < 0 || ind >= currSizeInBites || currSizeInBites == 0) {
            throw std::out_of_range("invalid index");
        } else {
            int byteNum = ind / 8;
            int bitNum = ind % 8;
            return (*((byte *) this->array + byteNum)) & (1 << (7 - bitNum));
        }
    }

    BitArray& operator=(const BitArray& source);//присвоение значения массива

    void resize(int numberOfBits, bool value = false);//изменение размера массива на длину nB, если nB>=0
    void clear();// обнуление массива
    void pushBack(bool bit);//добавление нового бита в конец

    BitArray& set(int n, bool val = true);//присваивает n-ному биту значение 1
    BitArray& set();//заполнение массива 1
    BitArray& reset(int n);//присваивает n-ному биту значение 0
    BitArray& reset();//заполнение массива 0

    BitArray& operator&=(const BitArray& source);//побитовое И для массивов одного размера, результат в первый массив
    BitArray& operator|=(const BitArray& source);//побитовое ИЛИ для массивов одного размера, результат в первый массив
    BitArray& operator^=(const BitArray& source);//побитовое ИСКЛ.ИЛИ для массивов одного размера, результат в первый массив

    BitArray& operator<<=(int n);//битовый сдвиг влево в оригинальном массиве
    BitArray& operator>>=(int n);//битовый сдвиг вправо в оригинальном массиве
    BitArray operator<<(int n) const;//битовый сдвиг влево -> новый массив
    BitArray operator>>(int n) const;//битовый сдвиг вправо -> новый массив

    [[nodiscard]] bool any() const;//true, если есть 1
    [[nodiscard]] bool none() const;//true, если нет 1
    [[nodiscard]] bool empty() const;//true, если массив пустой

    BitArray operator~() const;//битовая инверсия

    [[nodiscard]] int count() const;//количество ненулевых битов
    Bit operator[](int i);//возвращает/присваивает значение i-того бита
    [[nodiscard]] int size() const;//количество битов в массиве

    [[nodiscard]] std::string toString() const;//byte->char, возвращает строку массива
};

template<typename blockType>//true, если массивы равны
bool operator==(const BitArray<blockType> & first, const BitArray<blockType> & second) {
    if (first.size() != second.size()) {
        return false;
    }
    for (int i = 0; i < first.size(); i++) {
        if (first.get(i) != second.get(i)) {
            return false;
        }
    }
    return true;
}

template<typename blockType>//true, если не равны
bool operator!=(const BitArray<blockType> & first, const BitArray<blockType> & second) {
    return !(first == second);
}

template<typename blockType>//битовое И, результат в новый массив
BitArray<blockType> operator&(const BitArray<blockType>& first, const BitArray<blockType>& second) {
    auto result = BitArray<blockType>(first);
    result &= second;
    return result;
}

template<typename blockType>//битовое ИЛИ, результат в новый массив
BitArray<blockType> operator|(const BitArray<blockType>& first, const BitArray<blockType>& second) {
    auto result = BitArray<blockType>(first);
    result |= second;
    return result;
}

template<typename blockType>//битовое ИСКЛ.ИЛИ, результат в новый массив
BitArray<blockType> operator^(const BitArray<blockType>& first, const BitArray<blockType>& second) {
    auto result = BitArray<blockType>(first);
    result ^= second;
    return result;
}

template<typename blockType>//true, если значения равны
bool operator==(const typename BitArray<blockType>::Bit &first, const typename BitArray<blockType>::Bit &second) {
    return first.value == second.value;
}

template<typename blockType>//true, если значения не равны
bool operator!=(const typename BitArray<blockType>::Bit &first, const typename BitArray<blockType>::Bit &second) {
    return !(first.value == second.value);
}

#endif //TASK1_BITARRAY_H