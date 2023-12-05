import pygame

# 为了在屏幕上绘制玩家的飞船，我们将加载一幅图像，再使用Pygame方法blit()绘制它。
# 在游戏中几乎可以使用任何类型的图像文件，但使用位图（.bmp）文件最为简单，因为Pygame默认加载位图。

class Ship:
    def __init__(self, ai_game):
        self.screen = ai_game.screen
        self.settings = ai_game.settings
        self.screen_rect = ai_game.screen.get_rect()

        self.image = pygame.image.load('images/ship.bmp')
        self.rect = self.image.get_rect()
        self.rect.midbottom = self.screen_rect.midbottom
        self.moving_right = False
        self.moving_left = False

        self.x = float(self.rect.x)

    def blitme(self):
        self.screen.blit(self.image, self.rect)
    # Pygame之所以高效，是因为它让你能够像处理矩形（rect对象）一样处理所有的游戏元素，即便其形状并非矩形。

    def update(self):
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.x += self.settings.ship_speed
        if self.moving_left and self.rect.left > self.screen_rect.left:
            self.x -= self.settings.ship_speed
        self.rect.x = self.x
