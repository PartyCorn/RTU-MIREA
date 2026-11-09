import java.util.Arrays;

public class GenericStack<E> {
    @SuppressWarnings("unchecked")
    private E[] array = (E[]) new Object[10];
    private int size = 0;

    public int getSize() { return size; }

    public E peek() {
        return array[size - 1];
    }

    @SuppressWarnings("unchecked")
    public void push(E o) {
        if (size >= array.length) {
            E[] newArray = (E[]) new Object[array.length * 2];
            System.arraycopy(array, 0, newArray, 0, array.length);
            array = newArray;
        }
        array[size++] = o;
    }

    public E pop() {
        E o = array[--size];
        array[size] = null;
        return o;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public String toString() {
        return "стек: " + Arrays.toString(Arrays.copyOf(array, size));
    }
}
