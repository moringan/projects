import requests
API_TOKEN = "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"
API_URL = "https://api-inference.huggingface.co/models/ehartford/Wizard-Vicuna-13B-Uncensored"
headers = {"Authorization": f"Bearer {API_TOKEN}"}

def query(payload):
	response = requests.post(API_URL, headers=headers, json=payload)