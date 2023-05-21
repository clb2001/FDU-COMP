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
<title>购物车</title>
<link rel="stylesheet" href="<%=basePath%>/css/bootstrap.min.css" />
</head>
<body>
	<script type="text/javascript" src="js/jquery-2.0.3.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<jsp:include page="/header1.jsp"></jsp:include>
	<c:if test="${empty sessionScope.cart.items}">
		<div style="margin-left: 600px; margin-top: 100px">
			<img src="img/gwc.gif" />
			<h4 style="margin-left: 170px">
				<strong>空空如也！快去把喜欢的专辑添加进购物车吧！！！</strong> <a href="/client/ClientServlet?op=category">返回主页</a>
			</h4>
		</div>
	</c:if>
	<c:if test="${!empty sessionScope.cart.items}">
		<table class="table table-bordered table-hover"
			style="margin-left: 16px; width: 1890px">
			<tr>
				<th style="width: 100px">序号</th>
				<th style="width: 100px">音乐图片</th>
				<th style="width: 200px">音乐名称</th>
				<th style="width: 200px">音乐类型</th>
				<th style="width: 200px">音乐作者</th>
				<th style="width: 300px">音乐出版社</th>
				<th style="width: 200px">音乐单价</th>
				<th style="width: 200px">购买数量</th>
				<th style="width: 200px">小计</th>
				<th style="width: 200px">操作</th>
			</tr>
			<c:forEach items="${sessionScope.cart.items}" var="c" varStatus="vs">
				<tr class="active">
					<td style="margin-top: 50px">${vs.index+1}</td>
					<td><img style="width: 80px; height: 100px"
						src="${pageContext.request.contextPath}/img/${c.value.music.path}/${c.value.music.filename}" />
					</td>
					<td>《${c.value.music.music_name}》</td>
					<td>${c.value.music.category.category_name}</td>
					<td>${c.value.music.music_author}</td>
					<td>${c.value.music.music_press}</td>
					<td><span style="color: rgb(198, 46, 45); font-weight: bold">￥${c.value.music.music_price}</span></td>

					<td><input type="email" class="form-control" id="quantity"
						value="${c.value.quantity}"
						style="width: 45px; height: 30px; margin-left: 70px"
						onchange="changeNum(this,${c.value.quantity},'${c.value.music.music_id}')"></td>

					<td><span style="color: rgb(198, 46, 45); font-weight: bold">￥${c.value.money}</span></td>
					<td><a href="javascript:delOneItem('${c.value.music.music_id}')">删除</a></td>
				</tr>
			</c:forEach>
			<tr>
				<td colspan="10" style="padding-left: 1450px"><strong>总数量：<span
						style="color: rgb(198, 46, 45); font-weight: bold; font-size: 20px">${sessionScope.cart.totalQuantity}</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;合计：
				</strong><span
					style="color: rgb(198, 46, 45); font-weight: bold; font-size: 20px">￥${sessionScope.cart.totalMoney}</span>
					<button type="button" class="btn btn-danger"
						style="background-color: rgb(198, 46, 45); width: 160px; height: 43px; margin-left: 50px"
						onclick="window.location='<%=basePath%>/order/OrderServlet?op=generateOrder'">
						<span style="font-size: 16px">结算</span>
					</button></td>

			</tr>
		</table>

	</c:if>
	<script type="text/javascript">
		function changeNum(inputObj,oldNum,music_id){
			var sure = window.confirm("确定要修改数量吗?");
			if(sure){
				//修改新数量
				var num = inputObj.value;
					//验证：用户输入的必须是自然数。 字母\1.1\-1排除
				if(!/^[1-9][0-9]*$/.test(num)){
					alert("请输入正确的数量");
					return;
				}
				//提交给服务器修改该项的数量
				window.location.href="${pageContext.request.contextPath}/client/ClientServlet?op=changeNum&num="+num+"&music_id="+music_id;
			}else{
				//显示原来的值
				inputObj.value = oldNum;
			}
		}
		function delOneItem(music_id) {
			var sure = window.confirm("确定删除改选项吗？");
			if (sure) {
				window.location.href = "${pageContext.request.contextPath}/client/ClientServlet?op=delItem&music_id="
						+ music_id;
				alert("删除成功！！");
			}
		}
	</script>

</body>
</html>