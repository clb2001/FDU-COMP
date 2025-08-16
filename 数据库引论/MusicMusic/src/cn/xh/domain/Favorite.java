package cn.xh.domain;

import java.io.Serializable;

// ’≤ÿº–
public class Favorite implements Serializable {
	private String favorite_id;//  ’≤ÿœÓid
	private String user_id;
	private String music_id;
	private Music music;

	public Favorite() {
		super();
		// TODO Auto-generated constructor stub
	}

	public Favorite(String favorite_id, String user_id, String music_id, Music music) {
		super();
		this.favorite_id = favorite_id;
		this.user_id = user_id;
		this.music_id = music_id;
		this.music = music;
	}

	public String getFavorite_id() {
		return favorite_id;
	}
	public void setFavorite_id(String favorite_id) {
		this.favorite_id = favorite_id;
	}

	public String getUser_id() {
		return user_id;
	}
	public void setUser_id(String user_id) {
		this.user_id = user_id;
	}

	public String getMusic_id() {
		return music_id;
	}
	public void setMusic_id(String music_id) {
		this.music_id = music_id;
	}

	public Music getMusic() {
		return music;
	}
	public void setMusic(Music music) {
		this.music = music;
	}

	@Override
	public String toString() {
		return "Favorite{" +
				"favorite_id='" + favorite_id + '\'' +
				"user_id='" + user_id + '\'' +
				"music_id='" + music_id +
				'}';
	}
}
