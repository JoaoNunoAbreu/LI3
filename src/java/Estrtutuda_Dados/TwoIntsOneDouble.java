public class TwoIntsOneDouble{
    private int x;
    private int y;
    private double z;
    public TwoIntsOneDouble(){
        this.x = 0;
        this.y = 0;
        this.z = 0;
    }
    public TwoIntsOneDouble(int x, int y, double z){
        this.x = x;
        this.y = y;
        this.z = z;
    }
    public int getX(){
        return this.x;
    }
    public int getY(){
        return this.y;
    }
    public double getZ(){
        return this.z;
    }
    public void soma(TwoIntsOneDouble pair){
        this.x += pair.getX();
        this.y += pair.getY();
        this.z += pair.getZ();
    }
    public String toString(){
        return this.x + " " + this.y + " " + this.z;
    }
}
