import java.util.Scanner;

public class RedBlackTreeTest { // Вывод всего дерева
    public static void main(String[] args) {
        RedBlackTree bst = new RedBlackTree();
        Scanner in = new Scanner(System.in);
        int a;
        int i;
        System.out.println("Введите количество элементов");
        i = in.nextInt();
        System.out.println("Введите элементы дерева");
        for (int j = 0; j < i; j++) {
            a = in.nextInt();
            bst.insert(a);
            System.out.println();
            bst.prettyPrint();
        }
    }
}