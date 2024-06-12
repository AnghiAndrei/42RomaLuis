import NavView from "/static/js/views/NavView.js"
import View from "/static/js/views/View.js";

class OtherUsersView extends View {

	constructor() {
		super();
		this._navView = new NavView("Other users");
	}

	_generateUserList(users, listTitle) {
		if (!users || users.length === 0) return "";
		let html = `
			<table class="table table-sm table-hover mb-0">
				<thead class="table-dark">
					<tr>
						<th scope="col" class="text-center">
							<span class="fw-medium">${listTitle}</span>
						</th>
						<th>
						</th>
					</tr>
				</thead>
				<tbody>
		`;
		users.forEach(user => {
			html += `
				<tr>
					<td class="text-start ps-2 align-middle">
						<span>
							${user.username}
						</span>
					</td>
					<td class="text-end pe-2">
						<label  class="btn btn-outline-dark">
							<input type="submit" value="${user.username}" name="username" class="d-none">
							<span class="fw-medium text-uppercase">Remove</span>
						</label>
					</td>
				</tr>
			`
		});
		html += `
				</tbody>
			</table>
		`;
		return html;
	}

	_generateMarkup() {
		const html = `
			<div class="container mt-3 pb-3">
				${this._navView._generateMarkup()}
					<div class="col-12 col-md-8 col-lg-9">
						<h2>Manage Your Friend List</h2>
						<p>These are the users you can play with. You may add a user to the list by entering his username.</p>
						<div class="row">
							<div class="col-12 col-lg-6 mb-2">
								<form data-add="add-friend">
									<div class="input-group">
										<input type="search" name="username" placeholder="Username" autocomplete="username" class="form-control" required aria-label="Username">
										<button type="submit" class="btn btn-dark">
											<span class="fw-medium text-uppercase">Add</span>
										</button>
									</div>
								</form>
							</div>
							<div class="col-12 col-lg-6">
								<form data-remove="remove-friend">
									${this._generateUserList(this._data.friends, "Friend List")}
								</form>
							</div>
						</div>
						<hr class="border">
						<h2>Manage Blocked Users</h2>
						<p>This is your blocked users. You may add a user to the list by entering his username.</p>
						<p>If a user is on your blocked list, the following will happen:</p>
						<ul>
							<li>They cannot play with you.</li>
							<li>You cannot play with the user.</li>
							<li>They cannot contact you via a Zong chat.</li>
							<li>You cannot contact the user via a Zong chat.</li>
							<li>If the user was in your friend list, your friendship will be deleted.</li>
						</ul>
						<p>Basically, blocking a user completely negates any interaction you might have with them on Zong.</p>
						<div class="row">
							<div class="col-12 col-lg-6 mb-2">
								<form data-add="block-user">
									<div class="input-group">
										<input type="search" name="username" placeholder="Username" autocomplete="username" class="form-control" required aria-label="Username">
										<button type="submit" class="btn btn-dark">
											<span class="fw-medium text-uppercase">Block</span>
										</button>
									</div>
								</form>
							</div>
							<div class="col-12 col-lg-6">
								<form data-remove="unblock-user">
									${this._generateUserList(this._data.blockedUsers, "Blocked User List")}
								</form>
							</div>
						</div>
					</div>
				</div>
			</div>
		`
		return html;
	}

	addHandlerUsers(handler) {
		document.addEventListener("submit", event => {
			const form = event.target;
			if (!form.hasAttribute("data-add")) return ;
			event.stopPropagation();
			event.preventDefault();
			const action = form.dataset.add;
			const username = new FormData(form).get("username");
			handler(action, username);
		});
		document.addEventListener("submit", event => {
			const form = event.target;
			if (!form.hasAttribute("data-remove")) return ;
			event.stopPropagation();
			event.preventDefault();
			const action = form.dataset.remove;
			const username = event.submitter.value;
			handler(action, username);
		});
	}
};

export default new OtherUsersView();