/**
 * @file Vector.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 *
 * @version 2.0
 * @brief Templated dynamic array with auto growing and simple operations, minimal and completed
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>


    /**
     * @class Vector
     * @author Svetlana Alkhasova
     * @date 18/07/25
     * @version 2.0
     * @brief An expandable array that handles memory and lets you store any type.
     *
     * This is a basic custom vector class — it can grow if you add more items,
     * and lets you safely get/set values with []. Good for assignments where you
     * can’t use the STL vector by itself.
     *
     * @tparam T The type of things you want to store (like int, float, WeatherEntry, ...)
     */
template <typename T>
class Vector {
public:
        /**
         * @brief Creates an empty vector with space for at least n items.
         * @param n Initial capacity (defaults to 1 if not set or given <1)
         */
    Vector(int n = 1);

        /**
         * @brief Makes a vector with n copies of a given value.
         * @param n Number of elements to start with.
         * @param defaultValue The value to fill the vector with.
         */
    Vector(int n, const T& defaultValue);

        /**
         * @brief Copy constructor — makes a new vector as a full copy of another.
         * @param other The vector to copy from.
         */
    Vector(const Vector<T>& other);

        /**
         * @brief Assignment operator — replaces what's inside with another vector's stuff.
         * @param other The vector to copy from.
         * @return Reference to this vector after copying.
         */
    Vector<T>& operator=(const Vector<T>& other);

        /**
         * @brief Destructor, cleans up any memory used by the vector.
         */
    ~Vector();

        /**
         * @brief Adds a new item to the end of the vector.
         * resizes storage if needed.
         * @param element Value to add at the end.
         */
    void pushBack(const T& element);

        /**
         * @brief Removes one item from the end (if the vector isn’t empty).
         */
    void popBack();

        /**
         * @brief Clears the vector so it acts empty (but doesn’t free reserved space).
         */
    void Clear();

        /**
         * @brief Gets how many actual items are stored in the vector right now.
         * @return The count of elements.
         */
    int GetSize() const;

        /**
         * @brief Doubles the vector's capacity when there isn't enough space.
         *
         * Grows the underlying array but does not change your actual elements.
         * Called automatically if you pushBack past current capacity.
         */
    void resize();

        /**
         * @brief Lets you use square-brackets to get/set items by index.
         * @param index Which element to access (starts at 0)
         * @return Reference to the requested element.
         * @throws std::out_of_range if index is wrong.
         */
    T& operator[](int index);

        /**
         * @brief Same as above, but for read-only (const) access.
         */
    const T& operator[](int index) const;

private:
    T* data; ///< Points to the array storing the items
    int size; ///< How many elements are currently in use
    int capacity;///< How much space has been allocated (can be bigger than size)
};

//IMPLEMENTATION

template <typename T>
Vector<T>::Vector(int n) : size(0), capacity(n > 0 ? n : 1) {
    data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(int n, const T& defaultValue) : size(n), capacity(n > 0 ? n : 1) {
    data = new T[capacity];
    for (int i = 0; i < size; i++) data[i] = defaultValue;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) : size(other.size), capacity(other.capacity) {
    data = new T[capacity];
    for (int i = 0; i < size; i++) data[i] = other.data[i];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
    data = NULL;
    size = 0;
    capacity = 0;
}

template <typename T>
void Vector<T>::resize() {
    int newCapacity = capacity * 2;
    T* tmp = new T[newCapacity];
    for (int i = 0; i < size; i++) tmp[i] = data[i];
    delete[] data;
    data = tmp;
    capacity = newCapacity;
}

template <typename T>
void Vector<T>::pushBack(const T& element) {
    if (size == capacity) resize();
    data[size++] = element;
}

template <typename T>
void Vector<T>::popBack() {
    if (size > 0) size--;
}

template <typename T>
void Vector<T>::Clear() {
    size = 0;
}

template <typename T>
int Vector<T>::GetSize() const {
    return size;
}

template <typename T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

#endif // VECTOR_H
