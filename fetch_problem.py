import requests
import os

token = os.environ.get('ACMOJ_TOKEN')
url = "https://acm.sjtu.edu.cn/OnlineJudge/problem/1779"
headers = {"Authorization": f"Bearer {token}"} if token else {}
response = requests.get(url, headers=headers)
with open("problem_1779.html", "w") as f:
    f.write(response.text)
