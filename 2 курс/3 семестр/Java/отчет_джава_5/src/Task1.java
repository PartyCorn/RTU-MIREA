import java.util.ArrayList;
import java.util.Arrays;

public class Task1 {
    public static <E> ArrayList<E> removeDuplicates(ArrayList<E> list) {
        ArrayList<E> result = new ArrayList<>();
        for (E element : list) {
            if (!result.contains(element)) {
                result.add(element);
            }
        }
        return result;
    }

    public static <E> int linearSearch(E[] list, E key) {
        for (int i = 0; i < list.length; i++) {
            if (list[i].equals(key)) {
                return i;
            }
        }
        return -1;
    }

    public static <E extends Comparable<E>> E max(E[] list) {
        if (list == null || list.length == 0) return null;
        E maxElement = list[0];
        for (int i = 1; i < list.length; i++) {
            if (list[i].compareTo(maxElement) > 0) {
                maxElement = list[i];
            }
        }
        return maxElement;
    }

    public static <E extends Comparable<E>> E max(E[][] list) {
        if (list == null || list.length == 0) return null;
        E maxElement = list[0][0];
        for (int i = 0; i < list.length; i++) {
            for (int j = 0; j < list[i].length; j++) {
                if (list[i][j].compareTo(maxElement) > 0) {
                    maxElement = list[i][j];
                }
            }
        }
        return maxElement;
    }

    public static void main(String[] args) {
        ArrayList<String> words = new ArrayList<>(Arrays.asList("Java", "Код", "Java", "Стек", "Код"));
        System.out.println("1.1 Исходник: " + words);
        System.out.println("1.1 Без дубликатов: " + removeDuplicates(words));

        Integer[] numbers = {10, 25, 30, 45, 50};
        System.out.println("\n1.2 Позиция числа 30: " + linearSearch(numbers, 30));
        System.out.println("1.2 Позиция числа 99: " + linearSearch(numbers, 99));

        Circle[] circles = {new Circle(3.5), new Circle(7.2), new Circle(5.0)};
        System.out.println("\n1.3 Наибольший круг: " + max(circles));

        Integer[][] matrix = {
                {1, 5, 3},
                {9, 2, 8},
                {4, 7, 6}
        };
        System.out.println("\n1.4 Наибольший элемент в двумерном массиве: " + max(matrix));
    }
}
