@dataclass(slots=True)
class Vector:
    x: int | float | Fraction
    y: int | float | Fraction

    def __neg__(self) -> "Vector":
        return Vector(-self.x, -self.y)

    def __add__(self, other: "Vector") -> "Vector":
        return Vector(self.x + other.x, self.y + other.y)

    def __sub__(self, other: "Vector") -> "Vector":
        return Vector(self.x - other.x, self.y - other.y)

    def __mul__(self, k) -> "Vector":
        return Vector(self.x * k, self.y * k)

    def __rmul__(self, k) -> "Vector":
        return Vector(self.x * k, self.y * k)

    def __truediv__(self, k) -> "Vector":
        return Vector(self.x / k, self.y / k)

    def dot(self, other: "Vector"):
        return self.x * other.x + self.y * other.y

    def cross(self, other: "Vector"):
        return self.x * other.y - self.y * other.x

    def norm(self):  # use math.hypot for high accuracy
        return math.sqrt(self.x**2 + self.y**2)

    def dis(self, other: "Vector"):
        return (self - other).norm()

    def norm_square(self):  # faster for sorting int
        return self.x * self.x + self.y * self.y

    def dis_square(self, other: "Vector"):  # faster for sorting int
        return (self - other).norm_square()