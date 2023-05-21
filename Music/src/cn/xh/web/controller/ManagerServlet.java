package cn.xh.web.controller;

import cn.xh.domain.Administrator;
import cn.xh.domain.Music;
import cn.xh.domain.Category;
import cn.xh.domain.User;
import cn.xh.service.ManagerService;
import cn.xh.service.impl.ManagerServiceImpl;
import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.*;

@WebServlet("/admin/ManagerServlet")
public class ManagerServlet extends HttpServlet {
    private final ManagerService service = new ManagerServiceImpl();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setContentType("text/html;charset=UTF-8");
        String op = req.getParameter("op");

        if (op.equals("login")) {
            login(req, resp);
        }
        if (op.equals("managerInformation")) {
            managerInformation(req, resp);
        }
        if (op.equals("managerPassword")) {
            managerPassword(req, resp);
        }
        if (op.equals("layout")) {
            layout(req, resp);
        }
        if (op.equals("addMusicUI")) {
            addMusicUI(req, resp);
        }
        if (op.equals("addMusic")) {
            try {
                addMusic(req, resp);
            } catch (FileUploadException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        if (op.equals("addCategory")) {
            addCategory(req, resp);
        }
        if (op.equals("category")) {
            getCategoryMusic(req, resp);
        }
        if (op.equals("editMusicUI")) {
            editMusicUI(req, resp);
        }
        if (op.equals("editMusic")) {
            try {
                editMusic(req, resp);
            } catch (FileUploadException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        if (op.equals("delMusic")) {
            delMusic(req, resp);
        }
        if (op.equals("categoryList")) {
            categoryList(req, resp);
        }
        if (op.equals("editCategoryUI")) {
            editCategoryUI(req, resp);
        }
        if (op.equals("editCategory")) {
            editCategory(req, resp);
        }
        if (op.equals("delCategory")) {
            delCategory(req, resp);
        }
        if (op.equals("findUsers")) {
            findUsers(req, resp);
        }
        if (op.equals("addAdmin")) {
            addAdmin(req, resp);
        }
        if (op.equals("sales")) {
            sales(req, resp);
        }
    }

    private void sales(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        List<Music> sales = service.sales();
        req.setAttribute("sales", sales);
        req.getRequestDispatcher("/admin/sales.jsp").forward(req, resp);
    }

    private void addAdmin(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String name = req.getParameter("name");
        String sex = req.getParameter("sex");
        String tel = req.getParameter("tel");
        Administrator admin = new Administrator(username, password, name, sex, tel);
        service.addAdmin(admin);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>修改成功！</div>");
    }

    private void findUsers(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        List<User> list = service.findUsers();
        HttpSession session = req.getSession();
        session.setAttribute("users", list);
        req.getRequestDispatcher("/admin/managerUsers.jsp").forward(req, resp);
    }

    private void login(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        HttpSession session = req.getSession();
        Administrator admin = service.login(username, password);
        if (admin.getUsername() != null && !admin.getUsername().equals("")) {
            req.setAttribute("message", "登录成功");
            session.setAttribute("admin", admin);
            req.getRequestDispatcher("/admin/message.jsp").forward(req, resp);
        } else {
            resp.getWriter()
                    .write("无此用户，请联系管理员！！      <a href='/client/ClientServlet?op=category'>返回首页</a>");
        }

    }

    private void managerInformation(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String username = req.getParameter("username");
        String name = req.getParameter("name");
        String sex = req.getParameter("sex");
        String tel = req.getParameter("tel");
        service.managerInformation(username, name, sex, tel);
        HttpSession session = req.getSession();
        Administrator admin = (Administrator) session.getAttribute("admin");
        admin.setName(name);
        admin.setSex(sex);
        admin.setTel(tel);
        session.setAttribute("admin", admin);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>修改成功！</div>");

    }

    private void managerPassword(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String repassword = req.getParameter("repassword");

        service.managerPassword(username, password);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>修改成功！</div>");
    }

    private void layout(HttpServletRequest req, HttpServletResponse resp) {
        try {
            HttpSession session = req.getSession();
            session.removeAttribute("admin");
            resp.sendRedirect("/client/ClientServlet?op=category");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void addMusicUI(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        List<Category> categories = service.findAllCategory();
        req.setAttribute("cs", categories);
        req.getRequestDispatcher("/admin/addMusic.jsp").forward(req, resp);

    }

    private void addMusic(HttpServletRequest req, HttpServletResponse resp) throws FileUploadException, IOException {
        boolean isMultipart = ServletFileUpload.isMultipartContent(req);
        if (!isMultipart) {
            throw new RuntimeException("表单上传类型有误！！");
        }
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload sfu = new ServletFileUpload(factory);
        List<FileItem> items = new ArrayList<FileItem>();
        items = sfu.parseRequest(req);
        Music music = new Music();
        for (FileItem item : items) {
            if (item.isFormField()) {
                processFormField(item, req, music);
            } else {
                processUploadFile(item, req, music);
            }
        }
        service.addMusic(music);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>添加成功！</div>");
    }
    
    private void processUploadFile(FileItem item, HttpServletRequest req, Music music) {
        try {
            String dirImages = getServletContext().getRealPath("/images");
            String FieldName = item.getFieldName();
            String name = item.getName();
            String fileType = name.substring(name.lastIndexOf(".") + 1);
            String fileName = UUID.randomUUID().toString();
			Date time = new Date();
			SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
			String strTime = simpleDateFormat.format(time);
            String path = strTime +File.separator + "musics";
            String filename = fileName + "." + fileType;
            File fileDir = new File(dirImages, path + File.separator + filename);
            File parentDir = new File(dirImages, path);
            if (!parentDir.exists()) {
                parentDir.mkdirs();
            }
            music.setFilename(filename);
            music.setPath(path);

            InputStream inputStream = item.getInputStream();
            FileOutputStream fos = new FileOutputStream(fileDir);
            int len = 0;
            while ((len = inputStream.read()) != -1) {
                fos.write(len);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void processFormField(FileItem item, HttpServletRequest req, Music music) {
        try {
            String inputName = item.getFieldName();
            String inputValue = item.getString("UTF-8");
            if (inputName.equals("category_id")) {
                String category_id = item.getString();
                System.out.println("category_id=" + category_id);
                Category category = service.findCategoryById(category_id);
                System.out.println(category);
                music.setCategory(category);
            } else {
                BeanUtils.setProperty(music, inputName, inputValue);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void addCategory(HttpServletRequest req, HttpServletResponse resp) {
        try {
            Category category = new Category();
            BeanUtils.populate(category, req.getParameterMap());
            service.addCategory(category);
            resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                    + "/img/duigou.png'/>添加成功！</div>");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void getCategoryMusic(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        List<Music> musics = service.getCategoryMusic(req.getParameter("cid"));
        List<Category> categoryList = service.findAllCategory();
        req.setAttribute("musics", musics);
        req.setAttribute("categoryList", categoryList);
        req.getRequestDispatcher("/admin/musicsList.jsp").forward(req, resp);
    }

    private void editMusicUI(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String music_id = req.getParameter("music_id");
        Music music = findMusicById(music_id);
        List<Category> category = service.findAllCategory();
        HashMap map = new HashMap();
        map.put("music", music);
        map.put("category", category);
        req.setAttribute("map", map);
        req.getRequestDispatcher("/admin/editMusic.jsp").forward(req, resp);
    }

    private void editMusic(HttpServletRequest req, HttpServletResponse resp) throws FileUploadException, IOException {
        String music_id = req.getParameter("music_id");
        String music_name = req.getParameter("music_name");
        String music_singer = req.getParameter("music_singer");
        String music_lyricist = req.getParameter("music_lyricist");
        String music_composer = req.getParameter("music_composer");
        String record = req.getParameter("record");
        String record_company = req.getParameter("record_company");
        String music_description = req.getParameter("music_description");
        double music_price = Double.parseDouble(req.getParameter("music_price"));
        String music_inventory = req.getParameter("music_inventory");
        service.editMusic(music_id, music_name, music_singer, music_lyricist, music_composer, record,
                record_company, music_description, music_price, music_inventory);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>修改成功！</div>");
    }

    private void delMusic(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String music_id = req.getParameter("music_id");
        service.delMusic(music_id);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>删除成功！</div>");
    }

    private void categoryList(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        List<Category> categoryList = service.findAllCategory();
        req.setAttribute("categoryList", categoryList);
        req.getRequestDispatcher("/admin/categoriesList.jsp").forward(req, resp);
    }

    private void editCategoryUI(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        Category category = service.findCategoryById(req.getParameter("category_id"));
        req.setAttribute("category", category);
        req.getRequestDispatcher("/admin/editCategory.jsp").forward(req, resp);
    }

    private void editCategory(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        Category category = new Category(req.getParameter("category_id"), req.getParameter("category_name"),
                req.getParameter("category_description"));
        service.editCategory(category);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>修改成功！</div>");
    }

    private void delCategory(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String category_id = req.getParameter("category_id");
        service.delCategory(category_id);
        resp.getWriter().write("<div style='text-align: center;margin-top: 260px'><img src='" + req.getContextPath()
                + "/img/duigou.png'/>删除成功！</div>");
    }

    private Music findMusicById(String music_id) {
        return service.findMusicById(music_id);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
