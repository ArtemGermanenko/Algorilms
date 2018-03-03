import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

class Node{
    int iData;
    Node leftChild;
    Node rightChild;
    int height;
}

class Tree {

    public Node root;

    public Tree() {
        root = null;
    }

    public boolean find(int key) {
        Node current = root;
        if (root == null)
            return false;
        while (current.iData != key) {
            if (key < current.iData)
                current = current.leftChild;
            else
                current = current.rightChild;
            if (current == null)
                return false;
        }
        return true;
    }

    public int calcHeight(Node node) {
        if (node != null) {
            return node.height = Math.max(calcHeight(node.leftChild), calcHeight(node.rightChild)) + 1;
        } else {
            return -1;
        }
    }

    public void insert(int key) {
        Node newNode = new Node();
        newNode.iData = key;
        if (root == null)
            root = newNode;
        else {
            Node current = root;
            Node parent;
            while (true) {
                parent = current;
                if (key < current.iData) {
                    current = current.leftChild;
                    if (current == null) {
                        parent.leftChild = newNode;
                        return;
                    }
                } else {
                    current = current.rightChild;
                    if (current == null) {
                        parent.rightChild = newNode;
                        return;
                    }
                }
            }
        }
    }

    public Node delete_recursively(Node v, int x) {
        if (v == null)
            return null;
        if (root.iData == x) {
            root = root.rightChild;
            return root;
        }
        if (x < v.iData) {
            v.leftChild = delete_recursively(v.leftChild, x);
            return v;
        } else if (x > v.iData) {
            v.rightChild = delete_recursively(v.rightChild, x);
            return v;
        }
        if(calcHeight(v.rightChild) == calcHeight(v.leftChild)) {
            if (v.leftChild == null)
                return v.rightChild;
            else if (v.rightChild == null)
                return v.leftChild;
            else {
                int min_key = find_min(v.rightChild).iData;
                v.iData = min_key;
                v.rightChild = delete_recursively(v.rightChild, min_key);
            }
        }
        return v;
    }

    public Node find_min(Node v) {
        if (v.leftChild != null)
            return find_min(v.leftChild);
        else
            return v;
    }

    Stack<Integer> stack = new Stack<>();

    public Stack<Integer> contPreOrder(Node top) {
        if (top != null) {
            stack.push(top.iData);
            contPreOrder(top.leftChild);
            contPreOrder(top.rightChild);
        }
        return stack;
    }

    public List<List<Node>> levelOrder(Node root) {
        List<List<Node>> result = new ArrayList<List<Node>>();
        if (root == null) {
            return result;
        }
        Queue<Node> tmpQueue = new LinkedList<Node>();
        Stack<Queue<Node>> stack = new Stack<Queue<Node>>();
        Node tmp = root;
        tmpQueue.add(tmp);
        stack.push(tmpQueue);
        while (!stack.isEmpty()) {
            tmpQueue = stack.pop();
            Queue<Node> newQueue = new LinkedList<Node>();
            List<Node> list = new ArrayList<Node>();
            while (!tmpQueue.isEmpty()) {
                tmp = tmpQueue.poll();
                list.add(tmp);
                if (tmp.leftChild != null) {
                    newQueue.add(tmp.leftChild);
                }
                if (tmp.rightChild != null) {
                    newQueue.add(tmp.rightChild);
                }
            }
            if (!newQueue.isEmpty()) {
                stack.push(newQueue);
            }
            result.add(list);
        }
        tmp = null;
        tmpQueue = null;
        return result;
    }

    public int findAverage(List<Node> list){
        list.sort(new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                return o1.iData - o2.iData;
            }
        });
        return list.get((list.size()/2)).iData;
    }

    public Set<Integer> remake(int[] mass){
        Set<Integer> list = new LinkedHashSet<>();
        for (int i = mass.length-1; i >=0; i--) {
            list.add(mass[i]);
        }
        return list;
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        Tree newtree = new Tree();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("in.txt"), StandardCharsets.UTF_8))) {
            String line;
            while ((line = reader.readLine()) != null) {
                int curent = Integer.parseInt(line);
                if (!newtree.find(curent))
                    newtree.insert(curent);
            }
        } catch (IOException e) {
        }
        int average = 0;
        int height = newtree.calcHeight(newtree.root);
        int floorHeight = (int) Math.floor(height / 2);
        List<List<Node>> list = newtree.levelOrder(newtree.root);
        List<Node> level = list.get(height - floorHeight);
        for (int i = 0; i < level.size(); i++) {
            if (newtree.calcHeight(level.get(i).rightChild) != newtree.calcHeight(level.get(i).leftChild))
                level.remove(i);
        }
        if (level.size() == 2) {
            PrintWriter writer = new PrintWriter("out.txt", "UTF-8");
            Stack<Integer> stack = newtree.contPreOrder(newtree.root);
            int[] mass = new int[stack.size()];
            int i = 0;
            while (!stack.empty()) {
                mass[i] = stack.peek();
                stack.pop();
                i++;
            }
            for (int j = mass.length - 1; j >= 0; j--) {
                writer.println(mass[j]);
            }
            writer.close();
        }
        if (level.size() % 2 != 0) {
            average = newtree.findAverage(level);
        }
        newtree.delete_recursively(newtree.root, average);
        PrintWriter writer = new PrintWriter("out.txt", "UTF-8");
        Stack<Integer> stack = newtree.contPreOrder(newtree.root);
        int[] mass = new int[stack.size()];
        int i = 0;
        while (!stack.empty()) {
            mass[i] = stack.peek();
            stack.pop();
            i++;
        }
        Set<Integer> lList = newtree.remake(mass);
        Integer[] endAray = lList.toArray(new Integer[lList.size()]);
        for (int j = 0; j < endAray.length; j++) {
            writer.println(endAray[j]);
        }
        writer.close();
    }
}

