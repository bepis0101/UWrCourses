import random
from PIL import Image, ImageDraw

W = H = 256
NIEBO = (10, 12, 40, 255)


def gwiazdy(d, seed, n=60):
    rnd = random.Random(seed)
    for _ in range(n):
        x, y = rnd.randrange(W), rnd.randrange(H)
        r = rnd.choice((0, 0, 1))
        d.ellipse([x - r, y - r, x + r, y + r], fill=(255, 255, 255, 255))


def obraz1():
    """Planeta z pierścieniem na tle gwiazd."""
    im = Image.new("RGBA", (W, H), NIEBO)
    d = ImageDraw.Draw(im)
    gwiazdy(d, 1)
    d.ellipse([28, 108, 228, 148], outline=(230, 170, 90, 255), width=8)
    d.ellipse([68, 68, 188, 188], fill=(200, 80, 60, 255))
    d.rectangle([68, 100, 188, 112], fill=(225, 120, 80, 255))
    d.rectangle([68, 140, 188, 150], fill=(170, 60, 50, 255))
    maska = Image.new("L", (W, H), 0)
    ImageDraw.Draw(maska).ellipse([68, 68, 188, 188], fill=255)
    tlo = Image.new("RGBA", (W, H), NIEBO)
    gwiazdy(ImageDraw.Draw(tlo), 1)
    ImageDraw.Draw(tlo).ellipse([28, 108, 228, 148], outline=(230, 170, 90, 255), width=8)
    im = Image.composite(im, tlo, maska)
    d = ImageDraw.Draw(im)
    d.arc([28, 108, 228, 148], start=0, end=180, fill=(230, 170, 90, 255), width=8)
    return im


def obraz2():
    """Rakieta lecąca nad księżycem."""
    im = Image.new("RGBA", (W, H), NIEBO)
    d = ImageDraw.Draw(im)
    gwiazdy(d, 2)
    d.ellipse([-60, 170, 316, 420], fill=(170, 170, 180, 255))
    for x, y, r in ((60, 200, 14), (150, 215, 20), (220, 195, 10)):
        d.ellipse([x - r, y - r // 2, x + r, y + r // 2], fill=(130, 130, 140, 255))
    d.polygon([(116, 150), (140, 150), (128, 190)], fill=(255, 140, 0, 255))
    d.polygon([(121, 150), (135, 150), (128, 172)], fill=(255, 230, 80, 255))
    d.polygon([(110, 120), (96, 152), (114, 146)], fill=(200, 30, 40, 255))
    d.polygon([(146, 120), (160, 152), (142, 146)], fill=(200, 30, 40, 255))
    d.rounded_rectangle([110, 70, 146, 150], radius=10, fill=(235, 235, 240, 255))
    d.polygon([(110, 76), (146, 76), (128, 34)], fill=(200, 30, 40, 255))
    d.ellipse([118, 90, 138, 110], fill=(60, 160, 230, 255), outline=(90, 90, 100, 255), width=3)
    return im


for name, img in (("obraz1", obraz1()), ("obraz2", obraz2())):
    raw = img.tobytes()
    assert len(raw) == W * H * 4 == 256 * 1024
    with open(f"{name}.rgba", "wb") as f:
        f.write(raw)
    img.save(f"{name}.png")
    print(name, len(raw), "B")