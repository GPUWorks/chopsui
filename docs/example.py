#!/usr/bin/env python3
import OpenGL.GL as gl
import chopsui.stdui as stdui
import chopsui as sui
import random

@sui.type("random-container")
class RandomContainer(sui.Type, sui.gl.Drawable):
    def __init__(self):
        super().__init__(self)
        self.rng = random.Random()

    @sui.attr
    def seed(self, value: int): # type annotation used for parse-time validation
        self.rng.seed(value)

    def child(self, node: sui.Node):
        # Used to validate whether or not we're going to allow this sort of node
        # In this case we just have to assert that it's drawable
        is_drawable = node.has_type(stdui.gl.Drawable)
        return is_drawable and super().child(self, node)

    def draw(self, width, height):
        for child in self.children:
            w = self.rng.random() * width
            h = self.rng.random() * height
            x = self.rng.random() * (width - w)
            y = self.rng.random() * (height - h)
            with self.viewport(x, y, w, h):
                child.draw(w, h)

# Leaf means is the same as
# def child(self, node):
#     return False
@sui.type("box", leaf=True)
class Box(sui.Type, sui.gl.Drawable):
    def __init__(self):
        super().__init__(self)
        # automatically wired up attributes that don't need any custom logic
        self.attrs = {
            "color": sui.Color
        }

    def draw(self, width, height):
        gl.glClearColor(self.color.r, self.color.g, self.color.b)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT)

if __name__ == "main":
    sui = """
    window title="Python chopsui demo"
        random-container
            box color=red
            box color=blue
            box color=green
    """
    stdui.activate()
    window = sui.parse(sui)
    window.run()
