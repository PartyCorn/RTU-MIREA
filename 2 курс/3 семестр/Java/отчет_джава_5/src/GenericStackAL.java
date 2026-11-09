public class GenericStackAL<E> extends java.util.ArrayList<E> {
    public int getSize() {
        return size();
    }

    public E peek() {
        return get(getSize() - 1);
    }

    @SuppressWarnings("unchecked")
    public void push(E o) {
        add(o);
    }

    public E pop() {
        return remove(getSize() - 1);
    }

    @Override
    public String toString() {
        return "стек: " + super.toString();
    }
}
