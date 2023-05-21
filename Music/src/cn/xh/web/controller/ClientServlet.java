package cn.xh.web.controller;

import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import cn.xh.domain.Music;
import cn.xh.domain.Category;
import cn.xh.domain.Favorite;
import cn.xh.domain.User;
import cn.xh.service.ClientService;
import cn.xh.service.ManagerService;
import cn.xh.service.impl.ClientServiceImpl;
import cn.xh.service.impl.ManagerServiceImpl;
import cn.xh.web.formbean.Cart;
import cn.xh.web.formbean.CartItem;

@WebServlet("/client/ClientServlet")
public class ClientServlet extends HttpServlet {

	private final ClientService service = new ClientServiceImpl();
	private final ManagerService managerService = new ManagerServiceImpl();

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		req.setCharacterEncoding("UTF-8");
		resp.setContentType("text/html;charset=UTF-8");
		String op = req.getParameter("op");// 得到传过来的请求
		if (op != null && !op.equals("")) {
			if (op.equals("login")) {
				login(req, resp);
			}
			if (op.equals("layout")) {
				layout(req, resp);
			}
			if (op.equals("register")) {
				register(req, resp);
			}
			if (op.equals("category")) {
				getCategoryMusic(req, resp);
			}
			if (op.equals("personInformation")) {
				personInformation(req, resp);
			}
			if (op.equals("personPassword")) {
				personPassword(req, resp);
			}
			if (op.equals("search")) {
				search(req, resp);
			}
			if (op.equals("particulars")) {
				particulars(req, resp);
			}
			if (op.equals("addCart")) {
				addCart(req, resp);
			}
			if (op.equals("delItem")) {
				delItem(req, resp);
			}
			if (op.equals("changeNum")) {
				changeNum(req, resp);
			}
			if (op.equals("addFavorite")) {
				addFavorite(req, resp);
			}
			if (op.equals("showFavorite")) {
				showFavorite(req, resp);
			}
			if (op.equals("delFavorite")) {
				delFavorite(req, resp);
			}
			if (op.equals("buyNow")) {
				buyNow(req, resp);
			}

		}
	}

	private void delFavorite(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
		String music_id = req.getParameter("music_id");
		service.delFavorite(music_id);
		HttpSession session = req.getSession();
		List<Favorite> lists = (List<Favorite>) session.getAttribute("favorite");
		Iterator<Favorite> iterator = lists.iterator();
		while (iterator.hasNext()) {
			Favorite favorite = iterator.next();
			if (music_id.equals(favorite.getMusic().getMusic_id())) {
				iterator.remove();
			}
		}
		resp.sendRedirect(req.getContextPath() + "/favorite.jsp");
	}

	private void showFavorite(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		HttpSession session = req.getSession();
		User user = (User) session.getAttribute("user");
		List<Favorite> favorites = service.findFavoriteByUserId(user);
		session.setAttribute("favorite", favorites);
		req.getRequestDispatcher("/favorite.jsp").forward(req, resp);
	}

	private void addFavorite(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		HttpSession session = req.getSession();
		User user = (User) session.getAttribute("user");
		String user_id = user.getId();
		String music_id = req.getParameter("music_id");
		boolean isExit = service.findFavorite(user_id, music_id);
		if (isExit == false) {
			service.addFavorite(user_id, music_id);
		}
	}

	private void changeNum(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		String num = req.getParameter("num");
		String music_id = req.getParameter("music_id");
		Cart cart = (Cart) req.getSession().getAttribute("cart");
		CartItem item = cart.getItems().get(music_id);
		item.setQuantity(Integer.parseInt(num));
		resp.sendRedirect(req.getContextPath() + "/showCart.jsp");

	}

	private void login(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		String username = req.getParameter("username");
		String password = req.getParameter("password");
		HttpSession session = req.getSession();
		User user = service.login(username, password);
		if (user.getUsername() != null && user.getUsername() != "") {
			req.setAttribute("message", "登录成功");
			session.setAttribute("user", user);
			req.getRequestDispatcher("/message.jsp").forward(req, resp);
		} else {
			req.setAttribute("message", "用户名或密码错误，请重新登录");
			req.getRequestDispatcher("/message.jsp").forward(req, resp);
		}
	}

	private void layout(HttpServletRequest req, HttpServletResponse resp) {
		try {
			HttpSession session = req.getSession();
			session.removeAttribute("user");
			resp.sendRedirect("/client/ClientServlet?op=category");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void register(HttpServletRequest req, HttpServletResponse resp) {
		try {
			String username = req.getParameter("username");
			String password = req.getParameter("password");
			String name = req.getParameter("name");
			String sex = req.getParameter("sex");
			String tel = req.getParameter("tel");
			String address = req.getParameter("address");
			boolean isExist = false;

			if (!username.equals("") && !password.equals("")) {
				isExist = service.register(username, password, name, sex, tel, address);
				if (isExist == true) {
					resp.getWriter().write("该用户已经注册，请直接");
					resp.getWriter().write("<a href='" + req.getContextPath() + "/client/ClientServlet?op=category'>登录</a>");
				} else {
					resp.getWriter().write("注册成功!");
					resp.getWriter().write("2s后跳往登录页");
					resp.setHeader("Refresh", "2;URL=" + req.getContextPath() + "/client/ClientServlet?op=category");
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void getCategoryMusic(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		List<Music> musics = service.getCategoryMusic(req.getParameter("cid"));
		req.setAttribute("musics", musics);
		List<Category> categoryList= managerService.findAllCategory();
		req.setAttribute("categoryList", categoryList);
		req.getRequestDispatcher("/showMusic.jsp").forward(req, resp);
	}

	private void personInformation(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		String username = req.getParameter("username");
		String name = req.getParameter("name");
		String sex = req.getParameter("sex");
		String tel = req.getParameter("tel");
		String address = req.getParameter("address");

		service.personInformation(username, name, sex, tel, address);
		resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
				+ "/img/duigou.png'/>修改成功！</div>");
	}

	private void personPassword(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		String username = req.getParameter("username");
		String password = req.getParameter("password");
		String repassword = req.getParameter("repassword");

		service.personPassword(password, username);
		resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
				+ "/img/duigou.png'/>修改成功！</div>");
	}

	private void search(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		String search = req.getParameter("search");
		List<Music> searchmessage = service.search(search);
		req.setAttribute("musics", searchmessage);
		req.getRequestDispatcher("/showMusic.jsp").forward(req, resp);
	}

	private void particulars(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		String music_id = req.getParameter("music_id");
		Music music = findMusicById(music_id);
		req.setAttribute("music", music);
		req.getRequestDispatcher("/particulars.jsp").forward(req, resp);
	}

	private Music findMusicById(String music_id) {
		Music music = service.findMusicById(music_id);
		return music;
	}

	private void addCart(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		String music_id = req.getParameter("music_id");
		Music music = findMusicById(music_id);
		HttpSession session = req.getSession();
		Cart cart = (Cart) session.getAttribute("cart");
		if (cart == null) {
			cart = new Cart();
			session.setAttribute("cart", cart);
		}
		cart.addMusic(music);
	}

	private void delItem(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		String music_id = req.getParameter("music_id");
		Cart cart = (Cart) req.getSession().getAttribute("cart");
		cart.getItems().remove(music_id);
		resp.sendRedirect(req.getContextPath() + "/showCart.jsp");
	}

	private void buyNow(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		String music_id = req.getParameter("music_id");
		Music music = findMusicById(music_id);
		HttpSession session = req.getSession();
		Cart cart = new Cart();
		session.setAttribute("buyNowMusic", cart);
		cart.addMusic(music);
		resp.sendRedirect(req.getContextPath() + "/buyNow.jsp");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		doGet(req, resp);
	}
}
