import java.time.Year;
import java.util.Scanner;

public class DaysInMonth {
    public static void main(String[] args) {
        String[] months = {"январь", "февраль", "март", "апрель", "май", "июнь",
                           "июль", "август", "сентябрь", "октябрь", "ноябрь", "декабрь"};
        int[] dom = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        Scanner sc = new Scanner(System.in);
        System.out.println("Введите номер месяца от 1 до 12: ");

        try {
            if (!sc.hasNextInt()) {
                System.out.println("Введено не целое число");
                return;
            }

            int monthNum = sc.nextInt();

            String month = months[monthNum - 1];
            int days = dom[monthNum - 1];

            if (monthNum == 2) {
                System.out.print("Вы выбрали февраль. Введите год для проверки: ");

                if (!sc.hasNextInt()) {
                    System.out.println("Введен некорректный год");
                    return;
                }

                int year = sc.nextInt();
                if (Year.isLeap(year)) { // (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                    days = 29;
                }
            }

            System.out.println("Месяц: " + month + ", количество дней: " + days);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Месяца с таким номером нет");
        } finally {
            sc.close();
        }
    }
}
