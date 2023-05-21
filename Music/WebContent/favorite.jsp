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
<title>收藏夹</title>
<link rel="stylesheet" href="<%=basePath%>/css/bootstrap.min.css" />
</head>
<body>
	<script type="text/javascript" src="js/jquery-2.0.3.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<script type="text/javascript">
		function delOne(music_id) {
			var sure = window.confirm("确定删除此专辑吗？");
			if (sure) {
				window.location.href = "${pageContext.request.contextPath}/client/ClientServlet?op=delFavorite&music_id=" + music_id;
				alert("删除成功！");
			}
		}
	</script>
	<jsp:include page="/header1.jsp"></jsp:include>
	<c:if test="${empty favorite}">
		<div style="margin-left: 600px; margin-top: 100px">
			<img src="<%=basePath%>/img/scj.gif" />
			<h4 style="margin-left: 170px">
				<strong>空空如也，快去把喜欢的专辑添加进收藏夹吧！</strong> <a
					href="<%=basePath%>/client/ClientServlet?op=category">返回主页</a>
			</h4>
		</div>
	</c:if>
	<c:if test="${!empty favorite}">
		<table class="table table-bordered table-hover"
			style="margin-left: 16px; width: 1890px">
			<tr>
				<th style="width: 100px">音乐编号</th>
				<th style="width: 100px">专辑图片</th>
				<th style="width: 200px">音乐名称</th>
				<th style="width: 200px">音乐类型</th>
				<th style="width: 200px">演唱</th>
				<th style="width: 200px">作词</th>
				<th style="width: 200px">作曲</th>
				<th style="width: 200px">所属专辑</th>
				<th style="width: 300px">唱片公司</th>
				<th style="width: 200px">专辑价格</th>
				<th style="width: 200px">操作</th>
			</tr>
			<c:forEach items="${favorite}" var="f" varStatus="vs">
				<tr class="active">
					<td style="margin-top: 50px">${vs.index+1}</td>
					<td><img style="width: 80px; height: 100px"
						src="${pageContext.request.contextPath}/img/${f.music.path}/${f.music.filename}" />
					</td>
					<td>${c.value.music.music_name}</td>
					<td>${c.value.music.category.category_name}</td>
					<td>${c.value.music.music_singer}</td>
					<td>${c.value.music.music_lyricist}</td>
					<td>${c.value.music.music_composer}</td>
					<td>${c.value.music.record}</td>
					<td>${c.value.music.record_music}</td>
					<td><span style="color: rgb(198, 46, 45); font-weight: bold">￥${f.music.music_price}</span></td>
					<td><a href="javascript:delOne('${f.music.music_id}')">删除</a></td>
				</tr>
			</c:forEach>
		</table>
	</c:if>
</body>
</html>