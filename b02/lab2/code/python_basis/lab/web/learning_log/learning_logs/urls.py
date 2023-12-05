"""定义learning_logs的URL模式"""
from django.urls import path
from . import views

urlpatterns = [
    # 主页
    path('', views.index, name='index'),
    path('topics/', views.topics, name='topics'),
]
