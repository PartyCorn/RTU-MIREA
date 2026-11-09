import java.util.ArrayList;

public class MyStack implements Cloneable {
    private ArrayList<Object> list = new ArrayList<>();

    public int getSize() { return list.size(); }

    public void push(Object o) { list.add(o); }

    public Object peek() {
        return list.get(getSize() - 1);
    }

    public Object pop() {
        Object o = list.get(getSize() - 1);
        list.remove(getSize() - 1);
        return o;
    }

    public boolean isEmpty() { return list.isEmpty(); }

    @Override
    @SuppressWarnings("unchecked")
    public Object clone() {
        try {
            // поверхностная копия объекта MyStack
            MyStack stackClone = (MyStack) super.clone();
            // глубокая копия поля списка ArrayList
            stackClone.list = (ArrayList<Object>) this.list.clone();
            return stackClone;
        } catch (CloneNotSupportedException ex) {
            return null;
        }
    }

    @Override
    public String toString() {
        return "стек: " + list.toString();
    }
}
