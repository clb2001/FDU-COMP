<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
			 ;
%>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>编辑音乐信息</title>
<link rel="stylesheet" href="<%=basePath%>/css/bootstrap.min.css" />
</head>
<body>
	<script type="text/javascript" src="js/jquery-2.0.3.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<div>
		<p style="font-size: 25px; margin-top: 20px; margin-left: 42px">编辑音乐信息</p>
	</div>
	<hr
		style="height: 10px; border: none; border-top: 10px groove #bd7bde;" />

	<div style="margin-top: 30px; margin-left: 430px">
		<form action="<%=basePath%>/admin/ManagerServlet?op=editMusic"
			method="post">
			<div class="form-group">
				<input type="hidden" class="form-control" id="music_id" name="music_id"
					value="${map.music.music_id}" style="width: 700px">
			</div>
			<div class="form-group">
				<label>音乐名称：</label> <input type="text" class="form-control"
					id="music_name" name="music_name" value="${map.music.music_name}"
					style="width: 700px">
			</div>
			<div class="form-group">
				<label>演唱：</label> <input type="text" class="form-control"
					id="music_singer" name="music_singer" value="${map.music.music_singer}"
					style="width: 700px">
			</div>
			<div class="form-group">
				<label>作词：</label> <input type="text" class="form-control"
											id="music_lyricist" name="music_lyricist" value="${map.music.music_lyricist}"
											style="width: 700px">
			</div>
			<div class="form-group">
				<label>作曲：</label> <input type="text" class="form-control"
											id="music_composer" name="music_composer" value="${map.music.music_composer}"
											style="width: 700px">
			</div>
			<div class="form-group">
				<label>所属专辑：</label> <input type="text" class="form-control"
											id="record" name="record" value="${map.music.record}"
											style="width: 700px">
			</div>
			<div class="form-group">
				<label>唱片公司：</label> <input type="text" class="form-control"
					id="record_company" name="record_company" value="${map.music.record_company}"
					style="width: 700px">
			</div>
			<div class="form-group">
				<label>音乐分类：</label> <select class="form-control" name="category_id"
					title="音乐分类" style="width: 700px">
					<option selected="selected">${map.music.category.category_name}</option>
					<c:forEach items="${map.category}" var="c">
						<option value="${c.category_id}">${c.category_name}</option>
					</c:forEach>
				</select>
			</div>
			<div class="form-group">
				<label for="exampleInputFile">图片上传：</label> <img
					style="width: 80px; height: 100px"
					src="${pageContext.request.contextPath}/img/${map.music.path}/${map.music.filename}" /><input
					type="file" id="file" name="file">
			</div>
			<div class="form-group">
				<label>音乐简介：</label>
				<textarea class="form-control" rows="3" id="music_description"
					name="music_description" style="width: 700px">${map.music.music_description}</textarea>
			</div>
			<div class="form-group">
				<label>专辑单价：</label> <input type="text" class="form-control"
					id="music_price" name="music_price" value="${map.music.music_price}"
					style="width: 700px">
			</div>
			<div class="form-group">
				<label>专辑库存：</label> <input type="text" class="form-control"
					id="music_inventory" name="music_inventory"
					value="${map.music.music_inventory}" style="width: 700px">
			</div>
			<br>
			<button type="submit" class="btn btn-default"
				onclick="window.location='manager/ManagerServlet?op=editMusic'">提交</button>
			<button type="button" class="btn btn-default" data-dismiss="modal"
				style="margin-left: 100px" onclick="history.go(-1);">关闭</button>
		</form>
	</div>
</body>
</html>