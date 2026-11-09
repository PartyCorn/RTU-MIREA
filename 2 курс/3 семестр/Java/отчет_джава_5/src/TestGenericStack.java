import java.util.Scanner;

public class TestGenericStack {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        GenericStackAL<String> stack = new GenericStackAL<>();

        System.out.println("Введите 5 строк:");
        for (int i = 0; i < 5; i++) {
            System.out.print("Строка " + (i + 1) + ": ");
            stack.push(scanner.nextLine());
        }

        System.out.println("\nСтроки в обратном порядке:");
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }
    }
}
