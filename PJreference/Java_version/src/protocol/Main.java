package protocol;

import java.io.IOException;

public class Main {
    private static int host1Port = 808;    // host 1占用端口

    private static int host2Port = 809;

    public static void main(String[] args) throws IOException {
//        startSR();
//        startStopAndWait();
//        startGBN();
//        startDual();
    }

//    private static void startSR() throws IOException {
//        MyHost sender = new SRHost(host1Port, 6, 50, 3, "Sender");
//        sender.setDestPort(host2Port);
//        MyHost receiver = new SRHost(host2Port, 6, 50, 3, "Receiver");
//
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    receiver.receive();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        }).start();
//
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    sender.sendData();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        }).start();
//    }
//
//    private static void startStopAndWait() throws IOException {
//        MyHost sender = new GBNHost(host1Port, 1, 20, 3, "Sender");
//        sender.setDestPort(host2Port);
//        MyHost receiver = new GBNHost(host2Port, 1, 20, 3, "Receiver");
//
//        new Thread(() -> {
//            try {
//                receiver.receive();
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }).start();
//
//        new Thread(() -> {
//            try {
//                sender.sendData();
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }).start();
//    }
//
//    private static void startGBN() throws IOException {
//        MyHost sender = new GBNHost(host1Port, 5, 20, 3, "Sender");
//        sender.setDestPort(host2Port);
//        MyHost receiver = new GBNHost(host2Port, 5, 20, 3, "Receiver");
//
//        new Thread(() -> {
//            try {
//                receiver.receive();
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }).start();
//
//        new Thread(() -> {
//            try {
//                sender.sendData();
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }).start();
//    }
//
//    private static void startDual() throws IOException {
//
//        GBNHost host1 = new GBNHost(host1Port, 5, 20, 3, "Host AAAA");
//        host1.setDestPort(host2Port);
//        GBNHost host2 = new GBNHost(host2Port, 8, 50, 3, "Host BBBB");
//        host2.setDestPort(host1Port);
//
//        // thread 2
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    host1.receive();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        }).start();
//
//        // thread 4
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    host2.receive();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        }).start();
//
//        // thread1
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    host1.sendData();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        }).start();
//
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    host2.sendData();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        }).start();
//    }


}
