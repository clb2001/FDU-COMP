package cn.xh.web.formbean;

import java.io.Serializable;

import cn.xh.domain.Music;

//购物项
public class CartItem implements Serializable {
	private final Music music;
	private int quantity;// 本项数量
	private double money;// 本项小计

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
