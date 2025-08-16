package cn.xh.web.formbean;

import java.io.Serializable;

import cn.xh.domain.Music;

//������
public class CartItem implements Serializable {
	private final Music music;
	private int quantity;// ��������
	private double money;// ����С��

	public CartItem(Music music) {
		this.music = music;
	}

	public int getQuantity() {
		return quantity;
	}

	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}

	public double getMoney() {
		return music.getMusic_price() * quantity;
	}

	public void setMoney(float money) {
		this.money = money;
	}

	public Music getMusic() {
		return music;
	}

}
