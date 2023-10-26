import pygame

pygame.init()
window_width = 900
window_length = 600
window = pygame.display.set_mode([window_width, window_length])
screen = pygame.display.get_surface()

clock = pygame.time.Clock()

while True:
    for event in pygame.event.get():
       if event.type == pygame.KEYDOWN:
           if event.key == pygame.K_ESCAPE:
               pygame.quit()


    pygame.display.update()
    





class Level:
    def DrawMap(self):
        pass


##screen.blit
##
