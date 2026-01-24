def submit(answer):
    url = "http://MATCH_SUBMIT_FLAG_URL"
    token = "TEAM_TOKEN"
    data = {"token": token, "answer": answer}
    s = requests.Seesion()
    resp = s.post(url, data=data, timeout=5)
    if "is true" in resp.content:
        print "OK:", token