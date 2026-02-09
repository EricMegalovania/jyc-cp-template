@dataclass
class Vector:
    x: int | float | Fraction
    y: int | float | Fraction

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y)

    def __mul__(self, k):
        return Vector(self.x * k, self.y * k)

    def __rmul__(self, k):
        return Vector(self.x * k, self.y * k)

    def __truediv__(self, k):
        return Vector(self.x / k, self.y / k)

    def dot(self, other):
        return self.x * other.x + self.y * other.y

    def cross(self, other):
        return self.x * other.y - self.y * other.x

    def norm(self):  # use math.hypot for high accuracy
        return math.sqrt(self.x**2 + self.y**2)

    def dis(self, other):
        return (self - other).norm()

    def norm_square(self):  # faster for sorting int
        return self.x * self.x + self.y * self.y

    def dis_square(self, other):  # faster for sorting int
        return (self - other).norm_square()