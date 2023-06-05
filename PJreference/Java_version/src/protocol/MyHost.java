package protocol;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public abstract class MyHost {
    /**
     * 窗口长度。
     */
    protected final int WINDOW_SIZE;

    /**
     * 分组个数。
     */
    protected final int DATA_NUMBER;

    /**
     * 超时时间，秒。
     */
    protected final int TIMEOUT;

    /**
     * 这个主机的名称。
     */
    protected String hostName;

    /*下面的是发送数据相关的变量*/

    /**
     * 下一个发送的分组。
     */
    protected int nextSeq = 1;

    /**
     * 当前窗口起始位置。
     */
    protected int base = 1;

    /**
     * 分组发送的目标地址。
     */
    protected InetAddress destAddress;

    /**
     * 发送分组的目标端口，初始化为80
     */
    protected int destPort = 80;

    /*接收数据相关*/

    /**
     * 期望收到的分组序列号。
     */
    protected int expectedSeq = 1;

    /*Sockets*/

    /**
     * 发送数据使用的socket。
     */
    protected DatagramSocket sendSocket;

    /**
     * 接收分组使用的socket。
     */
    protected DatagramSocket receiveSocket;

    public MyHost(int RECEIVE_PORT, int WINDOW_SIZE,
                  int DATA_NUMBER, int TIMEOUT, String name) throws IOException {
        this.WINDOW_SIZE = WINDOW_SIZE;
        this.DATA_NUMBER = DATA_NUMBER;
        this.TIMEOUT = TIMEOUT;
        this.hostName = name;

        sendSocket = new DatagramSocket();
        receiveSocket = new DatagramSocket(RECEIVE_PORT);
        destAddress = InetAddress.getLocalHost();
    }

    /**
     * 获得目标地址。
     *
     * @return 返回目标地址
     */
    public InetAddress getDestAddress() {
        return destAddress;
    }

    /**
     * 设置发送分组的目标地址。
     *
     * @param destAddress 目标地址
     */
    public void setDestAddress(InetAddress destAddress) {
        this.destAddress = destAddress;
    }

    /**
     * 获得目标端口。
     *
     * @return 目标端口，int
     */
    public int getDestPort() {
        return destPort;
    }

    /**
     * 设置目标端口。
     *
     * @param destPort 目标端口
     */
    public void setDestPort(int destPort) {
        this.destPort = destPort;
    }


    public abstract void sendData() throws IOException;

    public abstract void timeOut() throws IOException;

    public abstract void receive() throws IOException;

    /**
     * 向发送方回应ACK。
     *
     * @param seq    ACK序列号
     * @param toAddr 目的地址
     * @param toPort 目的端口
     * @throws IOException socket相关错误时抛出
     */
    protected void sendACK(int seq, InetAddress toAddr, int toPort) throws IOException {
        String response = hostName + " responses ACK: " + seq;
        byte[] responseData = response.getBytes();
        // 获得来源IP地址和端口，确定发给谁
        DatagramPacket responsePacket = new DatagramPacket(responseData, responseData.length, toAddr, toPort);
        receiveSocket.send(responsePacket);
    }

    public String getHostName() {
        return hostName;
    }
}
