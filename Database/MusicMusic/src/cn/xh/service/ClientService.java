package cn.xh.service;

import java.util.List;

import cn.xh.domain.Music;
import cn.xh.domain.Favorite;
import cn.xh.domain.User;

public interface ClientService {

	User login(String username, String password);

	boolean register(String username, String password, String name, String sex, String tel, String address);

	List<Music> getCategoryMusic(String cid);

	void personInformation(String username, String name, String sex, String tel, String address);

	void personPassword(String password, String username);

	List<Music> search(String search);

	Music findMusicById(String music_id);

	void addFavorite(String user_id, String music_id);

	List<Favorite> findFavoriteByUserId(User user);

	boolean findFavorite(String user_id, String music_id);

	void delFavorite(String music_id);

}
