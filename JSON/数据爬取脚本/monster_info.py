# !usr/bin/env python
# -*- coding:utf-8 _*-
"""
@Time: 2022/11/26
@Author: Wang Yang
"""
import json
import requests
from bs4 import BeautifulSoup


maps = ["30.锻炎森林", "29.沉沦之沼", "28.漩涡之底", "27.水晶山",
            "26.湿地墓园", "25.湖心圣树", "24.多西亚王城", "23.巨虫原野",
            "22.诅咒群岛", "21.飓风之海", "20.须臾之境", "19.大空洞",
            "18.永望之殿", "17.暗月渊谷", "16.南部海域", "15.世界边缘",
            "14.遗忘之地", "13.迷雾城", "12.冰峰谷", "11.巨龙之路",
            "10.祭品村落", "9.王城", "8.季风平原", "7.幻境森林", "6.极寒之地",
            "5.湿地", "4.流放之路", "3.失落王城", "2.荒野", "1.庇护之地", ]


def get_url_of_map(url):
    """

    Args:
        url: The src url of wiki.

    Returns:
        res: The list of url of each map.

    """
    base_url = "https://wiki.biligame.com/"
    response = requests.get(url)
    page_text = response.text
    soup = BeautifulSoup(page_text, 'lxml')

    res = soup.select('div[class="menu-wrap wiki-menu-ul-1 clearfix"] div[class="wiki-menu-li-1"]')
    res = [item for item in res if "主线" in item.a.text][0]
    res = res.select('a[class="menu-title"]')
    res = [item for item in res if item.text.strip() in maps]
    res = sorted(res, key=lambda x: int(x.text.strip().split('.')[0]))
    for item in res:
        print("\"" + item.text.strip() + "\"", base_url + item["href"])
    res = [base_url + item["href"] for item in res]
    return res


def get_data_of_monster(map, url):
    def get_data_step(tabel):
        lines = tabel.select('tr')

        name = lines[0].select('th')[0].text.strip('数据\n')
        print(name)

        attribute = {
            "体质": lines[1].select('td')[3].text.strip(),
            "力量": lines[1].select('td')[1].text.strip(),
            "魔力": lines[2].select('td')[1].text.strip(),
            "技巧": lines[3].select('td')[1].text.strip(),
            "速度": lines[4].select('td')[1].text.strip(),
            "护甲": lines[2].select('td')[3].text.strip(),
            "抗性": lines[3].select('td')[3].text.strip(),
            "种族": lines[4].select('td')[3].text.strip(),
        }

        skill = {lines[1].select('td')[4].text.strip(): lines[2].select('td')[4].text.strip()}
        if len(lines[1].select('td')) >= 6:
            skill.update({lines[1].select('td')[5].text.strip(): lines[2].select('td')[5].text.strip()})
        if len(lines[1].select('td')) >= 7:
            skill.update({lines[1].select('td')[6].text.strip(): lines[2].select('td')[6].text.strip()})
        if len(lines[1].select('td')) >= 8:
            skill.update({lines[1].select('td')[7].text.strip(): lines[2].select('td')[7].text.strip()})

        return {
            "monster_name": name,
            "monster_attribute": attribute,
            "monster_skill": skill
        }

    response = requests.get(url)
    page_text = response.text
    soup = BeautifulSoup(page_text, 'lxml')

    res = {"map": map, "monster": []}
    tabel_list = soup.select('div[class="visible-md visible-sm visible-lg"] table')

    for tabel in tabel_list:
        res["monster"].append(get_data_step(tabel))
    return res


if __name__ == "__main__":
    src_url = "https://wiki.biligame.com/dxcb2/%E9%A6%96%E9%A1%B5"
    urls = get_url_of_map(src_url)
    data = []
    for map, url in zip(maps[::-1], urls):
        print(map)
        data.append(get_data_of_monster(map, url))
    with open('monster_info.json', 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=4, ensure_ascii=False)
