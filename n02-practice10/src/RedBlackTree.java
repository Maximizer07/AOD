import java.util.Scanner;
class Node { // структура данных, представляющая собой узел в дереве
    int data;
    Node parent;
    Node left;
    Node right;
    int color;
}
public class RedBlackTree { // класс RedBlackTree реализует операции в красно-черном дереве
    private Node root;
    private Node TNULL;
    private void fixInsert(Node k){ // исправляет красно-черное дерево
        Node u;
        while (k.parent.color == 1) {
            if (k.parent == k.parent.parent.right) {
                u = k.parent.parent.left;
                if (u.color == 1) {
                    u.color = 0;
                    k.parent.color = 0;
                    k.parent.parent.color = 1;
                    k = k.parent.parent;
                } else {
                    if (k == k.parent.left) {
                        k = k.parent;
                        rightRotate(k);
                    }
                    k.parent.color = 0;
                    k.parent.parent.color = 1;
                    leftRotate(k.parent.parent);
                }
            } else {
                u = k.parent.parent.right;
                if (u.color == 1) {
                    u.color = 0;
                    k.parent.color = 0;
                    k.parent.parent.color = 1;
                    k = k.parent.parent;
                } else {
                    if (k == k.parent.right) {
                        k = k.parent;
                        leftRotate(k);
                    }
                    k.parent.color = 0;
                    k.parent.parent.color = 1;
                    rightRotate(k.parent.parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root.color = 0;
    }
    private void printHelper(Node root, String indent, boolean last) { // выводит древовидну структуру на экран
        if (root != TNULL) {
            System.out.print(indent);
            if (last) {
                System.out.print("    ");
                indent += " ";
            } else {
                System.out.print("    ");
                indent += " ";
            }
            String sColor = root.color == 1?"red":"black";
            System.out.println(root.data + "-" + sColor);
            printHelper(root.left, indent, false);
            printHelper(root.right, indent, true);
        }
    }
    public RedBlackTree() {
        TNULL = new Node();
        TNULL.color = 0;
        TNULL.left = null;
        TNULL.right = null;
        root = TNULL;
    }
    public void leftRotate(Node x) { // поворот влево в узле x
        Node y = x.right;
        x.right = y.left;
        if (y.left != TNULL) {
            y.left.parent = x;
        }
        y.parent = x.parent;
        if (x.parent == null) {
            this.root = y;
        } else if (x == x.parent.left) {
            x.parent.left = y;
        } else {
            x.parent.right = y;
        }
        y.left = x;
        x.parent = y;
    }
    public void rightRotate(Node x) { // поворот вправо в узле x
        Node y = x.left;
        x.left = y.right;
        if (y.right != TNULL) {
            y.right.parent = x;
        }
        y.parent = x.parent;
        if (x.parent == null) {
            this.root = y;
        } else if (x == x.parent.right) {
            x.parent.right = y;
        } else {
            x.parent.left = y;
        }
        y.right = x;
        x.parent = y;
    }
    public void insert(int key) { // Обычная Вставка Двоичного Поиска
        Node node = new Node();
        node.parent = null;
        node.data = key;
        node.left = TNULL;
        node.right = TNULL;
        node.color = 1;
        Node y = null;
        Node x = this.root;
        while (x != TNULL) {
            y = x;
            if (node.data < x.data) {
                x = x.left;
            } else {
                x = x.right;
            }
        }
        node.parent = y;
        if (y == null) {
            root = node;
        } else if (node.data < y.data) {
            y.left = node;
        } else {
            y.right = node;
        }
        if (node.parent == null){
            node.color = 0;
            return;
        }
        if (node.parent.parent == null) {
            return;
        }
       // prettyPrint();// (1 вывод)
        fixInsert(node);
    }
    public void prettyPrint() { // выведит древовидную структуру на экран
        printHelper(this.root, "", true);
    }
}