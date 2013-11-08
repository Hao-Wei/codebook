public class AvlTreeSet<E extends Comparable<? super E>> {
  private AvlTreeNode<E> root;
  public AvlTreeSet() { root = null; }
  public int size() { return AvlTreeNode.getSize(root); }
  public boolean contains(E obj) { return contains(root, obj); }
  public boolean add(E obj) { if (!contains(obj)) { root = add(root, obj); return true; } else return false; }
  public boolean remove(E obj) { if (contains(obj)) { root = remove(root, obj); return true; } else return false; }
  
  private static <E extends Comparable<? super E>> AvlTreeNode<E> add(AvlTreeNode<E> node, E obj) {
    if (node == null) return new AvlTreeNode<E>(obj);
    else {
      int comp = obj.compareTo(node.object);
      if      (comp < 0) node.left = add(node.left, obj);
      else if (comp > 0) node.right = add(node.right, obj);
      // Else object already exists at this node; do nothing
      node.recalculate();
      return balance(node);
    }
  }
  
  private static <E extends Comparable<? super E>> boolean contains(AvlTreeNode<E> node, E obj) {
    while (true) {
      if (node == null) return false;
      else {
        int comp = obj.compareTo(node.object);
        if      (comp < 0) node = node.left;
        else if (comp > 0) node = node.right;
        else return true;  // Found at this node
      }
    }
  }
  
  private static <E extends Comparable<? super E>> AvlTreeNode<E> remove(AvlTreeNode<E> node, E obj) {
    if (node == null) return null;
    else {
      int comp = obj.compareTo(node.object);
      if      (comp < 0) node.left  = remove(node.left , obj);
      else if (comp > 0) node.right = remove(node.right, obj);
      else {
        if (node.left == null && node.right == null)
          return null;
        else if (node.left != null && node.right == null)
          node = node.left;
        else if (node.left == null && node.right == null)
          node = node.right;
        else {
          E neighbor = getSuccessor(node);
          node.object = neighbor;
          node.right = remove(node.right, neighbor);
        }
      }
      node.recalculate();
      return balance(node);
    }
  }
  
  private static <E extends Comparable<? super E>> AvlTreeNode<E> balance(AvlTreeNode<E> node) {
    int balance = node.getBalance();
    if (balance == -2) {
      if (node.left.getBalance() == +1) node.left = node.left.rotateLeft();
      node = node.rotateRight();
    } else if (balance == +2) {
      if (node.right.getBalance() == -1) node.right = node.right.rotateRight();
      node = node.rotateLeft();
    }
    return node;
  }
  
  private static <E extends Comparable<? super E>> E getSuccessor(AvlTreeNode<E> node) {
    if (node == null || node.right == null) return null;
    node = node.right;
    while (node.left != null) node = node.left;
    return node.object;
  }
}

class AvlTreeNode<E> {
  public E object;
  public int height, size;
  public AvlTreeNode<E> left, right;
  
  public AvlTreeNode(E obj) { object = obj; height = size = 1; }
  
  public void recalculate() {
    height = Math.max(getHeight(left), getHeight(right)) + 1;
    size = getSize(left) + getSize(right) + 1;
  }
  
  public AvlTreeNode<E> rotateLeft() {
    AvlTreeNode<E> root = this.right;
    this.right = root.left;
    root.left = this;
    this.recalculate();
    root.recalculate();
    return root;
  }
  
  public AvlTreeNode<E> rotateRight() {
    AvlTreeNode<E> root = this.left;
    this.left = root.right;
    root.right = this;
    this.recalculate();
    root.recalculate();
    return root;
  }
  
  public int getBalance() { return getHeight(right) - getHeight(left); }
  public static int getHeight(AvlTreeNode<?> node) { return node == null ? 0 : node.height; }
  public static int getSize(AvlTreeNode<?> node) { return node == null ? 0 : node.size; }
}
