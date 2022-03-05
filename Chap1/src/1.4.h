#pragma once
#include <stdexcept>
#include <corecrt_math.h>
#include <assert.h>
//////////////range-based for//////////////////
/// range-based for查找容器begin end的方式：
/// array对象，begin为array首地址，end为首地址+长度；
/// 类对象，查找类的begin end方法；
/// 否则试图使用全局的begin end方法；
/// 
/// 实现一个范围range-based for：
namespace Range {

	template<typename T>
	class m_iterator {
	public:
		using value_type = T;
		using size_type = size_t;

		m_iterator(size_type cur_start, value_type begin_val, value_type step_val) :
			m_cur(cur_start), m_value(begin_val), m_step(step_val) {
			m_value += (m_step * m_cur);
		}
		value_type operator*() const { return m_value; };
		bool operator!=(const m_iterator& rhs) const {
			return (m_cur != rhs.m_cur);
		}
		m_iterator& operator++() {
			m_value += m_step;
			++m_cur;
			return (*this);
		}
	private:
		size_type m_cur;
		value_type m_value;
		const value_type m_step;

	};

	template <typename T>
	class impl {
	public:
		using value_type = T;
		using reference = value_type&;
		using const_reference = const reference;
		using iterator = m_iterator<value_type>;
		using const_iterator = const m_iterator<value_type>;
		using size_type = typename m_iterator<value_type>::size_type;

		impl(value_type begin_val, value_type end_val, value_type step_val) :
			m_begin(begin_val), m_end(end_val), m_step(step_val), m_maxCount(get_adjusted_count()) {}

		size_type size() const {
			return m_maxCount;
		}
		const_iterator begin() const {
			return { 0, m_begin, m_step };
		}

		const_iterator end() const {
			return { m_maxCount, m_begin, m_step };
		}

	private:
		const value_type m_begin;
		const value_type m_end;
		const value_type m_step;
		const size_type m_maxCount;

		size_type get_adjusted_count() {
			assert(abs(m_step - 0) > 1e-10);
			if (m_step > 0 && m_begin >= m_end) {
				throw std::logic_error("End value must be greater than begin value!");
			}
			else if (m_step < 0 && m_begin <= m_end) {
				throw std::logic_error("End value must be less than begin value!");
			}

			size_type count = static_cast<size_type> ((m_end - m_begin) / m_step);
			if ((m_begin + m_step * count) != m_end) {
				++count;
			}
			return count;
		}
	};

	template<typename T>
	impl<T> range(T end) {
		return { {}, end, 1 };
	}

	template<typename T>
	impl<T> range(T begin, T end) {
		return { begin, end, 1 };
	}

	template<typename T, typename U>
	auto range(T begin, T end, U step) -> impl<decltype((begin + end) / step)> {
		return impl<decltype((begin + end) / step)>(begin, end, step);
	}
}
