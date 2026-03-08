---
tags:
  - coupling
---
What is **abstraction**?
The process of hiding complex implementation details, showing only the essential features of an object
- allows user to focus on what the object does instead of how it does it

**Pipeline**
Client —> Interface/Abstract Class (API) —> Concrete Implementations (Implementation A, B, C)

Whats the big idea?
- To enable minimal *coupling* between two classes within the same package
**Coupling** - how much one class depends on (“or knows about”) another class

What are some key benefits?
- Reduced complexity (hiding intricate logic)
- Increased reusability (Abstract components can be reused across different parts of application)
- Enhanced maintainability (Changes to implementation doesn’t affect client code)
- Improved testability (Abstractions are easier to mock and unit test)

Ex. The more methods “Main” can see AND call inside “StudentAccountService”, the more tightly coupled they are.
- tight coupling is a problem that gets worse over time.


Refactoring Example in code
```
Before: Direct Dependency (Highly coupled code)

class OrderProcessor {
	private PaymentGatewat paymentGateway; <— Concrete class dependency
	
	public OrderProcessor() {
		this.paymentGateway = new StripePaymentGateway(); <— Tightly coupled
	}
	
	public void process(Order order) {
		paymentGateway.charge(order.getAmount());
	}
}
```


```
After: Dependency Injection with Interface (Abstraction & Decoupling)

interface PaymentGatewat {
	void charge(Double amount);
}

class OrderProcessor {
	private PaymentGateway paymentGateway <— Interference dependency
	
	//Dependency Injection (CONSTRUCTOR)
	public OrderProcessor(PaymentGateway paymentGateway) {
		this.paymentGateway = paymentGateway; <— Decoupled
	}
	
	public void process(Order order) {
		paymentGateway.charge(order.getAmount());
	}
}
```
