package cn.xh.web.formbean;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

import cn.xh.domain.Music;

public class Cart implements Serializable {

	private final Map<String, CartItem> items = new HashMap<String, CartItem>();
	private int totalQuantity;
	private double totalMoney;

	public int getTotalQuantity() {
		totalQuantity = 0;
		for (Map.Entry<String, CartItem> me : items.entrySet()) {
			totalQuantity += me.getValue().getQuantity();
		}
		return totalQuantity;
	}

	public void setTotalQuantity(int totalQuantity) {
		this.totalQuantity = totalQuantity;
	}

	public double getTotalMoney() {
		totalMoney = 0;
		for (Map.Entry<String, CartItem> me : items.entrySet()) {
			totalMoney += me.getValue().getMoney();
		}
		return totalMoney;
	}

	public void setTotalMoney(double totalMoney) {
		this.totalMoney = totalMoney;
	}

	public Map<String, CartItem> getItems() {
		return items;
	}

	public void addMusic(Music music) {
		if (items.containsKey(music.getMusic_id())) {
			CartItem item = items.get(music.getMusic_id());
			item.setQuantity(item.getQuantity() + 1);
		} else {
			CartItem item = new CartItem(music);
			item.setQuantity(1);
			items.put(music.getMusic_id(), item);
		}
	}

}
