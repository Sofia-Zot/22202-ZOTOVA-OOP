#include "BitArray.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>

template<typename blockType>
BitArray<blockType>::~BitArray() {
    if (capacityInBytes != 0) {
        delete[] array;
    }
}

template<typename blockType>
BitArray<blockType>::BitArray() {
    currSizeInBites = 0;
    capacityInBites = bitsPerBlock;
    capacityInBytes = sizeof(blockType);
    array = new blockType[capacityInBytes / bytesPerBlock];
}

template<typename blockType>
BitArray<blockType>::BitArray(int numberOfBits, blockType value) {
    currSizeInBites = numberOfBits;
    capacityInBytes = std::max(size_t(ceil((double) numberOfBits / 8)), sizeof(blockType));
    capacityInBites = capacityInBytes * 8;
    array = new blockType[capacityInBytes / bytesPerBlock];
    array[0] = value;
}

template<typename blockType>
BitArray<blockType>::BitArray(const BitArray &source) {
    if (*this == source) {
        return;
    }
    currSizeInBites = source.currSizeInBites;
    capacityInBites = source.capacityInBites;
    capacityInBytes = source.capacityInBytes;
    array = new blockType[capacityInBytes / bytesPerBlock];
    memcpy(array, source.array, capacityInBytes);
}

template<typename blockType>
int BitArray<blockType>::lastUnusedByteInd() const {
    return ceil((double) currSizeInBites / 8);
}

template<typename blockType>
void BitArray<blockType>::reallocateArray(int numberOfBits) {
    if (numberOfBits < 0) {
        throw std::range_error("Error: invalid amount of bits");
    }
    int newCapacity = ceil(ceil((double) numberOfBits / 8) / bytesPerBlock) * bytesPerBlock;
    newCapacity = std::max(sizeof(blockType), size_t(newCapacity));
    if (newCapacity != capacityInBytes) {
        auto *tmp = (blockType *) realloc((void *) array, newCapacity);
        if (tmp != nullptr) {
            this->array = tmp;
        } else {
            throw std::runtime_error("Error: unable to reallocate memory");
        }
    }
    this->capacityInBites = numberOfBits == 0 ? bitsPerBlock : newCapacity * 8;
    this->capacityInBytes = newCapacity;
    this->currSizeInBites = numberOfBits;
}

template<typename blockType>
BitArray<blockType>::Bit::Bit(BitArray<blockType> *bitArray, int i) {
    this->bitArray = bitArray;
    index = i;
    value = bitArray->get(i);
}

template<typename blockType>
BitArray<blockType>::Bit::Bit(const BitArray::Bit &source) {
    bitArray = source.bitArray;
    index = source.index;
    value = source.value;
}

template<typename blockType>
BitArray<blockType>::Bit &BitArray<blockType>::Bit::operator=(bool v) {
    bitArray->set(index, v);
    return *this;
}

template<typename blockType>
BitArray<blockType>::Bit &BitArray<blockType>::Bit::operator=(const BitArray::Bit &source) {
    if (source == this) {
        return  *this;
    }
    this->value = source.value;
    this->index = source.index;
    return *this;
}

template<typename blockType>
void BitArray<blockType>::swap(BitArray &source) {
    if (source.currSizeInBites != this->currSizeInBites) {
        throw std::runtime_error("Error: invalid array size");
    }
    else {
        int lastByte = lastUnusedByteInd();
        for (int i = 0; i < lastByte; i++) {
            std::swap(*((byte *) this->array + i), *((byte *) source.array + i));
        }
    }
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator=(const BitArray &source) {
    if (this == &source) {
        return *this;
    }
    this->clear();
    for (int i = 0; i < source.currSizeInBites; i++) {
        this->pushBack(source.get(i));
    }
    return *this;
}

template<typename blockType>
void BitArray<blockType>::resize(int numberOfBits, bool value) {
    int oldSize = this->currSizeInBites;
    reallocateArray(numberOfBits);
    for (int i = oldSize; i < numberOfBits; i++) {
        set(i, value);
    }
}

template<typename blockType>
void BitArray<blockType>::clear() {
    this->currSizeInBites = 0;
}

template<typename blockType>
void BitArray<blockType>::pushBack(bool bit) {
    if (capacityInBites == currSizeInBites) {
        int old_size = currSizeInBites;
        reallocateArray(capacityInBites * 2);
        this->currSizeInBites = old_size;
    }
    this->set(currSizeInBites, bit);
    currSizeInBites++;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::set(int n, bool val) {
    if (n >= capacityInBites) {
        resize(n + 1);
    } else if (n < 0) {
        throw std::out_of_range("Error: invalid index");
    }
    int byteNum = n / 8;
    int bitNum = n % 8;
    byte mask = 1 << (7 - bitNum);
    *((byte*)this->array + byteNum) ^= (-val ^ *((byte*)this->array + byteNum)) & mask;
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::set() {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        *((byte *) array + i) |= 255;
    }
    return *this;
}

template<typename blockType>
BitArray<blockType>& BitArray<blockType>::reset(int n) {
    set(n, false);
    return *this;
}

template<typename blockType>
BitArray<blockType>& BitArray<blockType>::reset() {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        *((byte *) array + i) &= 0;
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator&=(const BitArray &source) {
    if (source.size() != this->size()) {
        throw std::runtime_error("Error: invalid array size");
    } else {
        int lastByte = lastUnusedByteInd();
        std::transform((byte*)this->array, (byte*)this->array + lastByte, (byte*)source.array, (byte*)this->array, std::bit_and<byte>());
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator|=(const BitArray &source) {
    if (source.size() != this->size()) {
        throw std::runtime_error("Error: invalid array size");
    } else {
        int lastByte = lastUnusedByteInd();
        std::transform((byte*)this->array, (byte*)this->array + lastByte, (byte*)source.array, (byte*)this->array, std::bit_or<byte>());
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator^=(const BitArray &source) {
    if (source.size() != this->size()) {
        throw std::runtime_error("Error: invalid array size");
    } else {
        int lastByte = lastUnusedByteInd();
        std::transform((byte*)this->array, (byte*)this->array + lastByte, (byte*)source.array, (byte*)this->array, std::bit_xor<byte>());
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator<<=(int n) {
    if (n == 0) {
        return *this;
    }
    for (int i = 0; i < currSizeInBites; i++) {
        set(i, (i + n >= currSizeInBites ? 0 : (*this).get(i + n)));
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator>>=(int n) {
    if (n == 0) {
        return *this;
    }
    for (int i = currSizeInBites - 1; i >= 0; i--) {
        set(i, (i - n < 0 ? 0 : (*this).get(i - n)));
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator<<(int n) const {
    auto res = BitArray<blockType>(*this);
    res <<= n;
    return res;
}

template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator>>(int n) const {
    auto res = BitArray<blockType>(*this);
    res >>= n;
    return res;
}

template<typename blockType>
bool BitArray<blockType>::any() const {
    int lastByte = lastUnusedByteInd();
    bool anyNonZero = std::any_of((byte*)array, (byte*)array + lastByte, [](byte value) { return value != 0; });

    if (anyNonZero && lastByte > 0) {
        int startBitIndex = (lastByte - 1) * 8;
        int endBitIndex = currSizeInBites;

        for (int i = startBitIndex; i < endBitIndex; i++) {
            if (get(i)) {
                return true;
            }
        }
    }

    return anyNonZero;
}

template<typename blockType>
bool BitArray<blockType>::none() const {
    int lastByte = lastUnusedByteInd();
    bool allZero = std::none_of((byte*)array, (byte*)array + lastByte, [](byte value) { return value != 0; });

    if (allZero && lastByte > 0) {
        int startBitIndex = (lastByte - 1) * 8;
        int endBitIndex = currSizeInBites;
        bool allFalse = true;
        for (int i = startBitIndex; i < endBitIndex; i++) {
            if (get(i)) {
                allFalse = false;
                break;
            }
        }
        return allFalse;
    }

    return allZero;
}

template<typename blockType>
bool BitArray<blockType>::empty() const {
    return size() == 0;
}

template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator~() const {
    auto result = BitArray<blockType>(*this);
    for (int i = 0; i < currSizeInBites; i++) {
        result.set(i, !(*this).get(i));
    }
    return result;
}

template<typename blockType>
int BitArray<blockType>::count() const {
    int result = 0;
    for (int i = 0; i < currSizeInBites; i++) {
        if ((*this).get(i)) {
            result++;
        }
    }
    return result;
}

template<typename blockType>
BitArray<blockType>::Bit BitArray<blockType>::operator[](int i) {
    if (i >= currSizeInBites) {
        resize(i + 1);
    } else if (i < 0) {
        throw std::out_of_range("Error: invalid index");
    }
    return Bit(this, i);
}

template<typename blockType>
int BitArray<blockType>::size() const {
    return this->currSizeInBites;
}

template<typename blockType>
std::string BitArray<blockType>::toString() const {
    std::string result;
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        char symb = (*((byte *) array + i));
        result.push_back(symb);
    }
    return result;
}