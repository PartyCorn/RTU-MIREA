import java.util.Scanner;
public class CurrencyConverter {
    public static void main(String[] args) {
        final double ROUBLES_PER_YUAN = 11.91; // курс покупки

        int yuan;       // сумма денег в китайских юанях
        double roubles; // сумма денег в российских рублях

        Scanner input = new Scanner(System.in);
        System.out.print("Введите цену в юанях: ");
        yuan = input.nextInt();

        roubles = ROUBLES_PER_YUAN * yuan;
        System.out.println("Цена в рублях: " + roubles);
    }
}
