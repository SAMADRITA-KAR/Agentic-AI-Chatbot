# ChatGPT using Artificial Intelligence

This is a simple chat-based question-answering system powered by OpenAI's GPT-3.5 Turbo model. The project allows users to input questions, and the AI model responds with relevant answers.

## Requirements

To run this project, you need to install the OpenAI Python library:
pip install openai

You also need a valid OpenAI API key to authenticate the requests to the GPT-3.5 Turbo model.

## Getting Started

1. Install the required dependencies mentioned above.
2. Replace `"YOUR_API_KEY"` in the code with your actual OpenAI API key.
3. Run the code, and the program will prompt you to enter a question.
4. The AI model will process the question and provide a response.

```python
import openai

# Replace "YOUR_API_KEY" with your actual OpenAI API key
openai.api_key = "YOUR_API_KEY"

q = input("Enter question: ")
completion = openai.ChatCompletion.create(
    model="gpt-3.5-turbo",
    messages=[{"role": "user", "content": q}]
)

print(completion.choices[0].message['content'])
```

# Note
Make sure to comply with OpenAI's usage policies and terms while using the GPT-3.5 Turbo model.

# Author
This ChatGPT using Artificial Intelligence project is authored by [Samadrita Kar].

