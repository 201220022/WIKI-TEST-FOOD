# !usr/bin/env python
# -*- coding:utf-8 _*-
"""
@Time: 2022/11/27
@Author: Wang Yang
"""
import re
import json
import requests
from bs4 import BeautifulSoup


immunes = ['古神诅咒免疫', '暗月诅咒免疫', '眩晕免疫', '流血免疫', '瘟疫免疫', '灼伤免疫',
           '技巧衰减免疫', '速度衰减免疫', '魔力衰减免疫', '力量衰减免疫', '护甲衰减免疫', '抗性衰减免疫']
attributes = ['命中率', '暴击率', '闪避率', '回复效果', '异常附加率']


def get_data_of_equipment(url):
    def get_data_step(equipment):
        def read_name(text):
            names = text.split("又叫：")
            if len(names) >= 2:
                return [text.split("又叫：")[0]], text.split("又叫：")[1].split(", ")
            return [text.split("又叫：")[0]], []

        def read_source(text):
            return text.replace(" ", "").split("\n\n\n")

        def read_immune(text):
            ans = []
            for immune in immunes:
                if immune in text:
                    ans.append(immune)
            return ans

        def read_ignore(text):
            ignore_armor = 0
            ignore_resistance = 0
            if re.findall(r'无视护甲\+\d+', text):
                ignore_armor = int(re.findall(r'无视护甲\+\d+', text)[0].split('+')[1])
            if re.findall(r'无视抗性\+\d+', text):
                ignore_resistance = int(re.findall(r'无视抗性\+\d+', text)[0].split('+')[1])
            return ignore_armor, ignore_resistance

        def read_attribute(text):
            text = text.split('，')
            ans = {}
            for attribute in attributes:
                ans.update({attribute:0})
                for item in text:
                    if attribute in item:
                        ans.update({attribute:int(re.compile(r'\d+').search(item).group())})
                        break
            return ans.values()

        def read_skill(text):
            text = text.replace(':', '：')
            # 卸负
            unload = re.findall(r'卸负.*\d+.*负面效果。', text)
            unload = 0 if not unload else int(re.findall(r'\d+', unload[0])[0])
            text = re.sub(r'卸负.*\d+.*负面效果。', '', text)
            # 回春
            treatment = re.findall(r'「统称」回春.*\d+.*重伤后失效。', text)
            treatment = 0 if not treatment else int(re.findall(r'\d+', treatment[0])[0])
            text = re.sub(r'「统称」回春.*\d+.*重伤后失效。', '', text)
            # 吸血
            vampire = re.findall(r'吸血\d+%', text)
            vampire = 0 if not vampire else int(re.findall(r'\d+', vampire[0])[0])
            text = re.sub(r'吸血\d+%', '', text)
            # 抑制
            inhibition = re.findall(r'「统称」治疗抑制.*\d+%。', text)
            inhibition = 0 if not inhibition else int(re.findall(r'\d+', inhibition[0])[0])
            text = re.sub(r'「统称」治疗抑制.*\d+%。', '', text)
            ans = {
                "卸负": unload,
                "回春": treatment,
                "吸血": vampire,
                "治疗抑制": inhibition,
                "特效": []
            }
            text = re.split('[\n。]', text)
            for item in text:
                if item:
                    cond = ["战斗开始", "发动物理攻击", "发动魔法攻击", "受到物理攻击", "受到魔法攻击", "使用回复技能"]
                    obj = ["自身", "我方全体", "敌方单体", "敌方全体"]
                    item.replace(':', '：')
                    tmp = {
                        "名称": item.split("：")[0],
                        "条件": "",
                        "概率": "",
                        "对象": "自身",
                        "效果": "",
                        "持续时间": -1,
                    }
                    if '：' not in item: break
                    if '「制作者：罗拉娜」' in item: break
                    item = item.split("：")[1]
                    tmp["内容"] = item
                    # 触发条件
                    for it in cond:
                        if it in item:
                            tmp["条件"] = it
                            break
                    if "物攻" in item: tmp["条件"] = cond[1]
                    # 计算概率
                    prob = re.findall(r'\d+%*概率', item)
                    prob = 100 if not prob else int(re.findall(r'\d+', prob[0])[0])
                    tmp["概率"] = prob
                    # 生效对象
                    for it in obj:
                        if it in obj:
                            tmp["对象"] = it
                            break
                    # 持续时间
                    dur = re.findall(r'持续\d+', item)
                    dur = -1 if not dur else int(re.findall(r'\d+', dur[0])[0])
                    tmp["持续时间"] = dur
                    ans['特效'].append(tmp)
            return ans.values()

        res = {
            "名称": "",
            "简称": [],
            "命中": 0,
            "闪避": 0,
            "暴击": 0,
            "回复": 0,
            "异常": 0,
            "吸血": 0,
            "卸负": 0,
            "无视护甲": 0,
            "无视抗性": 0,
            "治疗抑制": 0,
            "免疫": [],
            "特效": [],
            "来源": []
        }
        equipment_info = equipment.select('td')
        for idx, info in enumerate(equipment_info):
            text = info.text.strip()
            # 读取名称
            if idx == 0:
                res["名称"], res["简称"] = read_name(text)
            # 读取来源
            elif idx == 1:
                res["来源"] = read_source(text)
            # 读取免疫效果
            elif idx == 2:
                res["免疫"] = read_immune(text)
            # 读取装备无视
            elif idx == 3:
                res["无视护甲"], res["无视抗性"] = read_ignore(text)
            # 读取装备属性
            elif idx == 4:
                res["命中"], res["暴击"], res["闪避"], res["回复"], res["异常"] = read_attribute(text)
            # 读取装备特效
            else:
                res["卸负"], res["回复"], res["吸血"], res["治疗抑制"], res["特效"] = read_skill(text)
        return res

    response = requests.get(url)
    page_text = response.text
    soup = BeautifulSoup(page_text, 'lxml')

    res = []
    equipment_list = soup.select(
        'div[class="hidden-xs"] table[class="wikitable"] table[id="CardSelectTr"]'
    )[0].select('tr[class="divsort"]')
    for equipment in equipment_list:
        eq = get_data_step(equipment)
        if "蓝图" not in eq["名称"][0]:
            res.append(eq)
    return res


if __name__ == "__main__":
    url = "https://wiki.biligame.com/dxcb2/%E8%A3%85%E5%A4%87"
    data = get_data_of_equipment(url)
    with open('equipment_info.json', 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=4, ensure_ascii=False)
